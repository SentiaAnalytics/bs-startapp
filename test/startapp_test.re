open Tape;

type action =
  | Inc
  | IncAsync
  | Dec
  ;

let noEff _ => ();

test "should call render once on startup" (fun t => {
 t.plan 1; 
 let _dispatch = Startapp.make 
  init::5
  update::(fun _ s => (s, noEff))
  render::(fun s _ => t.ok (s == 5)) 
  ();
});


test "should update state and rerender on dispatch" (fun t => {
  t.plan 2; 
  let init = 5;
  let expected = ref 5;
  let update action state => switch action {
  | Inc => (state + 1, noEff)
  | _ => (state, noEff)
  };
  let render state _ => t.ok (state == !expected);
  let dispatch = Startapp.make ::init ::update ::render ();
  expected := 6;
  dispatch Inc;
 });
 
 test "should call the effect function" (fun t => {
  t.plan 3; 
  let init = 5;
  let expected = ref 5;
  let eff dispatch => 
  Promise.resolve Inc
    |> Promise.finally dispatch dispatch;
  let update action state => switch action {
  | Inc => (state + 1, noEff)
  | IncAsync => (state, eff)
  | Dec => (state - 1, noEff)
  };
  let render state _ => t.ok (state == !expected);
  let dispatch = Startapp.make ::init ::update ::render ();
  dispatch IncAsync;
  expected := 6;
 });