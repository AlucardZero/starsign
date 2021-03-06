#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string>
#include <cstring>

using namespace std;

int main (int argc, char *argv[])
{
  int i, result;
  char **adom_argv;
  
  string adom_path("./adom");
  string sage_path("./starsign.so");
  // Prepare to load library
  char *preload = getenv("LD_PRELOAD");

  if (preload == NULL)
  {
    result = setenv("LD_PRELOAD", sage_path.c_str(), 1);
  }

  else
  {
    string new_preload(preload);
    new_preload += ' ';
    new_preload += sage_path;
    result = setenv("LD_PRELOAD", new_preload.c_str(), 1);
  }

  if (result == -1)
  {
    printf("Unable to change LD_PRELOAD\n");
    exit(1);
  }


  // Try to get info on ADOM executable
  struct stat buf;
  result = stat(adom_path.c_str(), &buf);

  if (result != -1)      // Ignore errors (perhaps unwisely)
  {

    // Try to determine ADOM's version while we're at it
    const char *version;

    switch (buf.st_size)
    {
      case 2388548:
	version = "100";
	break;
      case 2556118:
	version = "110";
	break;
      case 2452608:
	version = "111";
	break;
      case 2240572:
	version = "1203"; // 32-bit debian
	break;
      case 2246972:
	version = "1204"; // 32-bit debian
	break;
      case 2250044:
	version = "1205"; // 32-bit debian
	break;
      case 2267132: // 32-bit Debian
        version = "1206";
        break;
      case 2301084: // 32-bit Debian
        version = "1207";
        break;
      case 2315196: // 32-bit Debian
        version = "1208";
        break;
      case 2383036: // 32-bit Debian
        version = "1209";
        break;
      case 2379196: // 32-bit Debian
        version = "12010";
        break;
      case 2378908: // 32-bit Debian
        version = "12011";
        break;
      case 2444316: // 32-bit Debian
        version = "12013";
        break;
      case 2457248: // 32-bit Debian non-noteye
        version = "12014";
        break;
      case 2471612: // 32-bit Debian non-noteye
        version = "12016";
        break;
      case 2490700: // 32-bit Debian non-noteye
        version = "12017";
        break;
      case 2492396: // 32-bit Debian non-noteye
        version = "12018";
        break;
      case 2495376: // 32-bit Debian non-noteye
        version = "12019";
        break;
       case 2495248: // 32-bit Debian non-noteye
        version = "12020";
        break;

      default:
	version = "0";
	break;
    }

    setenv("ADOM_VERSION", version, 1);
  }

  // Run ADOM
  adom_argv = new char*[argc - optind + 2];
  adom_argv[0] = strdup(adom_path.c_str());

  for (i = 0; i <= argc - optind; i++)
  {
    adom_argv[1+i] = argv[optind+i];
  }

  adom_argv[i] = NULL;
  execvp(adom_path.c_str(), adom_argv);
  perror("starsign: Unable to run ADOM");
  exit(1);
}
