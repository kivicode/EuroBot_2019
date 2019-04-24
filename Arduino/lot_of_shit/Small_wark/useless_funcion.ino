int param (String in, int side) { //work
  int param = side == 1 ? ( split(split(in, '(', 1), ',', 0).toInt()) : (split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt());
  return param;
}
