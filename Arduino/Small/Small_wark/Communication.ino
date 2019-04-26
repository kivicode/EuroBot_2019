int param (String in, int side) { //work
  int param = side == 1 ? ( split(split(in, '(', 1), ',', 0).toInt()) : (split(split(split(split(in, '(', 1), ',', 1), ')', 0), ' ', 1).toInt());
  return param;
}

String split(String StringToSplit, char SplitChar, int StringPartIndex) {
  StringToSplit += SplitChar;
  String originallyString = StringToSplit;
  String outString = "";
  for (int i1 = 0; i1 <= StringPartIndex; i1++)
  {
    outString = "";
    int SplitIndex = StringToSplit.indexOf(SplitChar);

    if (SplitIndex == -1)
    {
      return outString;
    }
    for (int i2 = 0; i2 < SplitIndex; i2++)
    {
      outString += StringToSplit.charAt(i2);
    }
    StringToSplit = StringToSplit.substring(StringToSplit.indexOf(SplitChar) + 1);
  }
  return outString;
}
