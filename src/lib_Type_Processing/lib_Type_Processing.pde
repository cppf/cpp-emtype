
byte[] buff = new byte[128];

void setup()
{
  PutString(buff, 0, "Hello World", TYPE_ZEROED_STRING);
  println(GetString(buff, 0, TYPE_ZEROED_STRING));
  println(buff[10]);
}

void draw()
{
}

