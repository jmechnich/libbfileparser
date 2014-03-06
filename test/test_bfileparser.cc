#include <BFileParser.hh>

#include <iostream>

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <openssl/md5.h>


unsigned long get_size_by_fd(int fd) {
    struct stat statbuf;
    if(fstat(fd, &statbuf) < 0) exit(-1);
    return statbuf.st_size;
}

int main( int argc, char** argv)
{
  std::string defFile = "ES7V1.10.def";
  std::string inFile  = "OneReg-000.KM6";
  std::string outFile = "test.KM6";
  
  BFileParser fp;
  
  // Test 1: load binary file definition
  if(!fp.loadDef( defFile.c_str()))
  {
    std::cout << "Could not open definition file '" << defFile << "'"
              << std::endl;
    return 1;
  }
  
  // Test 2: load binary file using definition
  if(!fp.loadFile( inFile.c_str()))
  {
    std::cout << "Could not load file '" << inFile << "'" << std::endl;
    return 2;
  }
  
  // Test 3: save binary file
  if(!fp.saveFile( outFile.c_str()))
  {
    std::cout << "Could not save file '" << outFile << "'" << std::endl;
    return 3;
  }
  
  // Test 4: compare md5 hashes of both files
  int fd1 = open( inFile.c_str(), O_RDONLY);
  if(fd1 < 0) return 4;
  int fd2 = open( outFile.c_str(), O_RDONLY);
  if(fd2 < 0) return 5;

  unsigned long size1 = get_size_by_fd(fd1);
  unsigned long size2 = get_size_by_fd(fd2);
  
  char* buf1 = (char*) mmap(0, size1, PROT_READ, MAP_SHARED, fd1, 0);
  char* buf2 = (char*) mmap(0, size2, PROT_READ, MAP_SHARED, fd2, 0);

  unsigned char res1[MD5_DIGEST_LENGTH];
  MD5((unsigned char*) buf1, size1, res1);
  unsigned char res2[MD5_DIGEST_LENGTH];
  MD5((unsigned char*) buf2, size2, res2);
  
  int ret = memcmp( res1, res2, MD5_DIGEST_LENGTH);
  if( ret!=0) return 6;
  
  return 0;
}
