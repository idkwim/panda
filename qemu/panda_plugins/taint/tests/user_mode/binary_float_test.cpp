/*
 * Simple test that reads in floating point number to be tainted,
 * does a floating point  operation (based on command line argument)
 * with a constant float number, and writes the new buffer to a file.
 */

#include "stdio.h"
#include "assert.h"
#include "math.h"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

void usage();
int read_float(float *f2);
int write_float(float *f3);
int write_int(int *f3);
int write_uint(uint *f3);

int main(int argc, char const *argv[]) {
  // Usage statements
  if (argc < 2) {
    usage();
    return -1;
  }

  // Option handler
  int option = atoi(argv[1]);
  if (option < 1 || option > 10) {
    usage();
    return -1;
  }

  int res = 0;
  float f1 = -187.33667, f2 = 0.0, f3 = 0.0;
  int i3 = 0;
  uint u3 = 0;

  res = read_float(&f2);
  if (res) return -1;

  switch (option) {
    case 1:
      //fadd
      f3 = f1 + f2;
      res = write_float(&f3);
      break;
    case 2:
      //fsub
      f3 = f1 - f2;
      res = write_float(&f3);
      break;
    case 3:
      //fmul
      f3 = f1 * f2;
      res = write_float(&f3);
      break;
    case 4:
      //fdiv
      f3 = f1 / f2;
      res = write_float(&f3);
      break;
    case 5:
      //fcmp
      f3 = (f1 < f2);
      res = write_float(&f3);
      break;
    case 6:
      //fptosi
      i3 = static_cast<int>(f2);
      res = write_int(&i3);
      break;
    case 7:
      //fptoui
      u3 = static_cast<uint>(f2);
      res = write_uint(&u3);
      break;
    case 8:
      // sin, cos, etc.
      f3 = sin(f2);
      res = write_float(&f3);
      break;
    case 9:
      f3 = ldexp(f2, 2);
      res = write_float(&f3);
      break;
    case 10:
      f3 = atan2(f2, 2);
      res = write_float(&f3);
      break;
    default:
      //ERROR should not happen
      return -1;
      break;
  }

  if (res) return -1;

  return 0;
}

void usage() {
  std::cout << "Usage: myprog test_#" << std::endl;
  std::cout << "Test numbers:" << std::endl;
  std::cout << "\t1 - fadd" << std::endl;
  std::cout << "\t2 - fsub" << std::endl;
  std::cout << "\t3 - fmul" << std::endl;
  std::cout << "\t4 - fdiv" << std::endl;
  std::cout << "\t5 - fcmp" << std::endl;
  std::cout << "\t6 - fptosi" << std::endl;
  std::cout << "\t7 - fptoui" << std::endl;
  std::cout << "\t8 - sin" << std::endl;
  std::cout << "\t9 - ldexp" << std::endl;
  std::cout << "\t10 - atan2" << std::endl;
}

int read_float(float *f2) {
  FILE *file = fopen("panda_plugins/taint/tests/user_mode/binary_float.bin", "r");
  assert(file);
  int bytes = fread(f2, sizeof(float), 1, file);
  fclose(file);
  if (bytes){
    printf("Reading floating point number: %f\n", *f2);
    return 0;
  }
  else {
    printf("ERROR reading from file\n");
    return 1;
  }
}

int write_float(float *f3) {
  std::ofstream out("panda_plugins/taint/tests/user_mode/float_test_output.txt");
  if(out.good()) {
    std::cout << "Writing floating point number: " << std::fixed << *f3 << std::endl;
    out << *f3 << std::endl;
    out.close();
    return 0;
  } else {
    std:: cout << "ERROR writing to file" << std::endl;
    return -1;
  }
}

int write_int(int *f3) {
  std::ofstream out("panda_plugins/taint/tests/user_mode/float_test_output.txt");
  if(out.good()) {
    std::cout << "Writing int number: " << std::fixed << *f3 << std::endl;
    out << *f3 << std::endl;
    out.close();
    return 0;
  } else {
    std:: cout << "ERROR writing to file" << std::endl;
    return -1;
  }
}

int write_uint(uint *f3) {
  std::ofstream out("panda_plugins/taint/tests/user_mode/float_test_output.txt");
  if(out.good()) {
    std::cout << "Writing unsigned int number: " << std::fixed << *f3 << std::endl;
    out << *f3 << std::endl;
    out.close();
    return 0;
  } else {
    std:: cout << "ERROR writing to file" << std::endl;
    return -1;
  }
}
