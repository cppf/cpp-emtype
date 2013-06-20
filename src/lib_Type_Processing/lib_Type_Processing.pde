
byte[] buff = new byte[128];

void setup()
{
  println(ToLong64((byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)0, (byte)20));
  PutBinFromHex(buff, 0, 8, GetHexFromBin(0, 8, TYPE_ADD_SPACE), TYPE_HAS_SPACE);
  println(GetHexFromBin(buff, 0, 8, TYPE_ADD_SPACE));
}

void draw()
{
}

