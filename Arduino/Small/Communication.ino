

String* split(String in, char delim) {
  in += "|";
  int count = 0;
  for (int i = 0; i < in.length(); i++) {
    if (in.charAt(i) == delim) {
      count++;
    }
  }

  String output[count];
  int last = 0;
  count = 0;

  for (int i = 0; i < in.length(); i++) {
    if (in.charAt(i) == delim) {
      output[count] = in.substring(last + 1, i);
      count++;
      last = i;
    }
  }
  return output;
}

struct Command readCommand() {
  Command output;
  String in = String(Serial.readString());
  String cmd = split(in, '(')[0];
  String regularExpression = cmd + "(%d)";
  int n = sscanf(in.c_str() , regularExpression.c_str(), &output.param);
  output.func = cmd;
  return output;
}
