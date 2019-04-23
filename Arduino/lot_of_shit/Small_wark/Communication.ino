String split2(String data, char separator, int index) {
  int maxIndex = data.length() - 1;
  int j = 0;
  String chunkVal = "";

  for (int i = 0; i <= maxIndex && j <= index; i++)
  {
    chunkVal.concat(data[i]);

    if (data[i] == separator)
    {
      j++;

      if (j > index)
      {
        chunkVal.trim();
        return chunkVal;
      }

      chunkVal = "";
    }
    else if ((i == maxIndex) && (j < index)) {
      chunkVal = "";
      return chunkVal;
    }
  }
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
