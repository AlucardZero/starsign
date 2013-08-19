#include "jaakkos.h"

/*
   This is the starsign selector hook callback.
   Ask the user for a month and randomize the day in that month.
   Alternatively, completely randomize the day ('?').
 */ 

void starsign_select() {
  int month;
  uint32_t BIRTHSIGN_ADDR = 0;
  uint32_t JUMP_TO = 0;

  // Get ADOM version number
  char *version = getenv("ADOM_VERSION");
  int adom_version = 0;

  if (version != NULL)
  {
    sscanf(version, "%i", &adom_version);
  }


  /*
     BIRTHSIGN_ADDR is the place in memory where the day of birth is stored.
     Its value in memory will be the in-game displayed value minus one.

     JUMP_TO is where to resume execution in the ADOM executable.

     See http://www.adom.de/forums/showthread.php/1134-Choosing-star-sign?p=72882#post72882
     for information on finding these offsets.
   */
  switch (adom_version) {
    case 111:
      BIRTHSIGN_ADDR = 0x82b61f0;
      JUMP_TO = 0x813ee80;
      break;

    case 100:
      BIRTHSIGN_ADDR = 0x82a66e4;
      JUMP_TO = 0x0813ace0;
      break;

    case 1203:
      BIRTHSIGN_ADDR = 0x8283d40;
      JUMP_TO = 0x081386d0;
      break;

    case 1204:
      BIRTHSIGN_ADDR = 0x8285d40;
      JUMP_TO = 0x08139fb0;
      break;

    case 1205:
      BIRTHSIGN_ADDR = 0x8286948;
      JUMP_TO = 0x0813a860;
      break;

    case 1206:
      BIRTHSIGN_ADDR = 0x828acbc;
      JUMP_TO = 0x0813bf70;
      break;

    case 1207:
      BIRTHSIGN_ADDR = 0x82921fc;
      JUMP_TO = 0x81405a0;
      break;

    case 1208:
      BIRTHSIGN_ADDR = 0x8295a60;
      JUMP_TO = 0x81418f0;
      break;

    case 1209:
      BIRTHSIGN_ADDR = 0x82a7d40;
      JUMP_TO = 0x81458a0;
      break;

    case 12010:
      BIRTHSIGN_ADDR = 0x82a7e40;
      JUMP_TO = 0x8145780;
      break;

    case 12011:
      BIRTHSIGN_ADDR = 0x82a6d20;
      JUMP_TO = 0x8144910;
      break;

    case 12013:
      BIRTHSIGN_ADDR = 0x82b8c90;
      JUMP_TO = 0x8144690;

    case 12014:
      BIRTHSIGN_ADDR = 0x82bbf34;
      JUMP_TO = 0x8145870;

    case 12016:
      BIRTHSIGN_ADDR = 0x82be774;
      JUMP_TO = 0x8149090;

    default:
      break;
  }

  if ((BIRTHSIGN_ADDR == 0) || (JUMP_TO == 0)) {
    printf("Don't know where to put the birth date or jump to.  Unknown ADOM version %i ?\n", adom_version);
    return;
  }

  do {
    printf("\033[2J\033[1;1H");

    printf("Select the month of your birth:\r\n"
        "\r\n"
        "  ? - random\r\n"
        "\r\n"
        "  A - Raven\r\n"
        "  B - Book\r\n"
        "  C - Wand\r\n"
        "  D - Unicorn\r\n"
        "  E - Salamander\r\n"
        "  F - Dragon\r\n"
        "  G - Sword\r\n"
        "  H - Falcon\r\n"
        "  I - Cup\r\n"
        "  J - Candle\r\n"
        "  K - Wolf\r\n"
        "  L - Tree\r\n"
        "\r\n"
        "> ");

    fflush(stdout);
    month = toupper(fgetc(stdin));
  } while(month != '?' && (month < 'A' || month > 'L'));

  printf("\033[2J");
  fflush(stdout);

  month = month == '?' ? 0 : month-'A'+1;

  if(!month) month = rand() % 12;
  else month--;

  *((uint16_t*)BIRTHSIGN_ADDR) = (unsigned int)(30*month + (rand()%30));
  ((void(*)())JUMP_TO)();
}

