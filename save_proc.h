#ifndef SAVE_PROC_H
#define SAVE_PROC_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


typedef enum {
	SAVE_STATUS_OK,
	SAVE_STATUS_SIGNATURE_MISMATCH,
	SAVE_STATUS_CHECKSUM_MISMATCH,
	
	SAVE_STATUS_FILE_FAILURE
} WDSaveStatus;

typedef enum {
	// TODO all unlock flags
	UNLOCK_TODO
} WDUnlock;

static const char* WDUnlockStr[] = {
	// TODO all unlocks by name
};

enum WDColor {
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_RED,
	COLOR_PINK,
	COLOR_PURPLE,
	COLOR_YELLOW
};

static const char* WDColorStr[] = {
	"Sky Blue",
	"Green", // TODO proper names for the rest
	"Red",
	"Pink",
	"Purple",
	"Yellow"
};

enum WDAccessory {
	// TODO all accessories by ID
	ACCESSORY_TODO
};

static const char* WDAccessoryStr[] = {
	// TODO all accessories by name
};

enum WDRoom {
	ROOM_LIVING_ROOM,
	ROOM_GARDEN,
	ROOM_BEDROOM, 
	ROOM_KITCHEN,
	ROOM_ROOFTOP
};

static const char* WDRoomStr[] = {
	"Living Room",
	"Garden",
	"Bedroom",
	"Kitchen",
	"Rooftop"
};

enum WDPersonalities {
	PERSONALITY_NAUGHTY,
	PERSONALITY_CHEERFUL,
	PERSONALITY_BIG_EATER,
	PERSONALITY_NEAT_FREAK
};

enum WDMiniGame {
	// TODO minigames by index
	MINIGAME_TODO
};

static const char* WDMiniGameStr[] = {
	// TODO minigames by name
};

enum WDMiniGameDifficulty {
	DIFFICULTY_EASY,
	DIFFICULTY_HARD
};

typedef struct {
	uint32_t    unlockFlags[10];        // see other doc for offsets to unlock
	uint16_t    nickname[11];           // 10 wchars + null terminator
	uint8_t     musicVolume;            // 0-127
	uint8_t     soundVolume;            // 0-127
	uint8_t     travelModeColor;        // 0-5, blue/green/red/pink/purple/yellow
	uint8_t     travelModeAccessory;    // TODO document enums
	uint8_t     travelModeRoom;         // TODO document enums
	uint8_t     dogAge;                 // 1-10
	int16_t     dogMood;                // -128-127
	uint8_t     dogPersonality[4];      // scores: [0]=naughty, [1]=cheerful, [2]=big eater, [3]=neat freak
	uint16_t    dogFriendship;          // 0-54999
	uint8_t     unk4C;                  // (compared to a random number every few seconds)
	uint8_t     _unk4D;                 //<! not accessed?
	uint16_t    dogHunger;              // 0=hungry, drains over time, foods add to it
	uint16_t    dogCleanliness;         // 0-251, grooming increases
	uint8_t     _unk52[2];              //<! not accessed?
	uint32_t    playTime;               // measured in frames, max 268435456
	uint16_t    minigameScores[30];     // TODO figure out array order, 2x3x5
	uint8_t     unk94;                  // possibly an array, purpose unknown
	uint8_t     unk95;                  // *
	uint8_t     unk96;                  // *
	uint8_t     unk97;                  // *
	uint8_t     unk98;                  // *
	uint8_t     unk99;                  // *
	uint8_t     unk9A;                  // *
	uint8_t     unk9B;                  // *
	uint8_t     _unk9C[2];              //<! not accessed?
	uint8_t     unk9E[21];              // array accessed, purpose unknown
	uint8_t     _unkB2[6];              //<! not accessed?
} WDSave;

WDSaveStatus WD_ImportSaveFile(WDSave* dst, const char* savfile_src);
WDSaveStatus WD_ExportSaveFile(const char* savfile_dst, const WDSave* src);

WDSaveStatus WD_ImportDataFile(WDSave* dst, const char* binfile_src);
WDSaveStatus WD_ExportDataFile(const char* binfile_dst, const WDSave* src);

static inline bool WD_IsUnlocked(WDSave* sav, WDUnlock unlockable) {
	return sav->unlockFlags[unlockable >> 5] & (1 << (unlockable & 31));
}

static inline void WD_SetUnlocked(WDSave* sav, WDUnlock unlockable, bool unlocked) {
	uint32_t bit = 1 << (unlockable & 31);
	if (unlocked) {
		sav->unlockFlags[unlockable >> 5] |= bit;
	} else {
		sav->unlockFlags[unlockable >> 5] &= ~bit;
	}
}

#endif
