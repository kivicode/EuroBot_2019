int param (String in, int side) { //work
  int param = side == 1 ? ( split(split(in, '(', 1), ',', 0).toInt()) : (split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt());
  return param;
}

void veseluha () {
  go_by_encoders(30, 30, -100, -100);
  go_by_encoders(70, 70, 100, 0);
  go_by_encoders(71, 0, 100, 0);
  go(200, 70);
  delay(500);
  go(0,0);
}

void to_shaiba () {
  
}
