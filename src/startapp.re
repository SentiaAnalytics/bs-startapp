external setTimeout : (unit => unit) => int => unit = "setTimeout" [@@bs.val];
let make 
  ::init 
  ::update 
  ::render 
  ::onAction=(fun _ => ())
  ::onUpdate=(fun _ => ())
  ::onLoad=(fun _ _ => ())
  _ => {
  let state = ref init;
  let rec dispatch a => {
    onAction a;
    let (nextState, eff) = update a !state;
    state := nextState;
    onUpdate !state;
    render !state dispatch;
    setTimeout (fun _ => eff dispatch) 1;
    ();
  };
  onLoad !state dispatch;
  render !state dispatch;
  dispatch;
}

