external setTimeout : (unit => unit) => int => unit = "setTimeout" [@@bs.val];
let make ::init ::update ::render _ => {
  let state = ref init;
  let rec dispatch a => {
    let (nextState, eff) = update a !state;
    state := nextState;
    render !state dispatch;
    setTimeout (fun _ => eff dispatch) 1;
    ();
  };

  render !state dispatch;
  dispatch;
}

