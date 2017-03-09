for (uint8_t i = 0; i < 20; i++) {
  buffer += client.read();
}

buffer.remove(0, 9); // remove "HTTP/1.0 "
buffer.remove(3);    // remove rest of string, just want status code
