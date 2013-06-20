
byte[] buff = new byte[128];

void setup()
{
  buff[1] = 0x04;
  PutUshort(buff, 0, 65535);
  println(GetUshort(buff, 0));
}

void draw()
{
}

