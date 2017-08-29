let make : 
  init:: 'state => 
  update::('action => 'state => ('state, ('action => unit) => unit)) => 
  render::('state => ('action => unit) => unit) => 
  onAction:: ('action => unit)? =>
  onUpdate:: ('state => unit)? =>
  onLoad:: ('state => ('action => unit) => unit)? =>
  unit => 
  ('action => unit);