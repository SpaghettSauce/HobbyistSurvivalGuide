#include <SdFat.h>

#define FILE_BASE_NAME "Data"
SdFat sd;
SdFile file;

namespace SD
{
  bool begin(byte CS){
    if(!sd.begin(CS, SD_SCK_MHZ(8))){
      return false;
    }
  
    const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
    char fileName[13] = FILE_BASE_NAME "00.csv";

    while (sd.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } 
  }
  if (!file.open(fileName, O_WRONLY | O_CREAT | O_EXCL)) {
    return false;
  }
  return true;
  }

  void print(const char* str)
  {
    file.write(str);
    file.sync();
  }
}