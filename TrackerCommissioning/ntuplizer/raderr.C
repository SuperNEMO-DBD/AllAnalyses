double raderr(double r)
{
  // Simple parameterisation of error on drift distance.
  //
  // Units are centimetres.
  //
  double p[]  = { 0.154003, -0.154948, 0.0572175, -0.00756805 };
  double err = p[3];
  for (int i=2; i>-1; i--)
  {
    err *= r;
    err += p[i];
  }
  return err;
}
