#ifndef SAVE_PROC_H
#define SAVE_PROC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "wd_def.h"


typedef struct {
	uint32_t    gameFlags[FLAG_NUM_U32S];                        // See WDGameFlag, WD_GetFlag, WD_SetFlag
	uint16_t    nickname[NICKNAME_BUF_LEN];                      // 10 wchars + null terminator
	uint8_t     musicVolume;                                     // 0-127
	uint8_t     soundVolume;                                     // 0-127
	uint8_t     travelModeColor;                                 // Enum 0-5, see WDColor
	uint8_t     travelModeAccessory;                             // Enum 0-17, see WDAccessory
	uint8_t     travelModeRoom;                                  // Enum 0-4, see WDRoom
	uint8_t     dogAge;                                          // 1-10 (years)
	int16_t     dogMood;                                         // -128-127
	uint8_t     dogPersonality[PERSONALITY_MAX];                 // Scores for each personality type, see WDPersonality
	uint16_t    dogFriendship;                                   // 0-54999
	uint8_t     unk4C;                                           // (compared to a random number every few seconds)
	uint8_t     _unk4D;                                          //<! not accessed? Padding?
	uint16_t    dogHunger;                                       // 0=hungry, drains over time, foods increases
	uint16_t    dogCleanliness;                                  // 0-251?, drains over time, grooming increases
	uint8_t     _unk52[2];                                       //<! not accessed? Padding?
	uint32_t    playTime;                                        // measured in frames @ 30 fps, max 268435456 (0x10000000)
	uint16_t    minigameScores[MINIGAME_MAX][DIFFICULTY_MAX];    // [game][difficulty], see WDMinigame / WDMinigameDifficulty
	uint8_t     unk94;                                           // (debug ほんやく = "translation")
	uint8_t     minigameWinCount;                                // Number of times the player has won a minigame
	uint8_t     unk96;                                           // (debug おていれ = "cleaning", however, it is not times player has cleaned Wappy)
	uint8_t     fedCount;                                        // Number of times the player has fed Wappy with any food
	uint8_t     minigamePlayCount;                               // Number of times the player has played any minigame
	uint8_t     petCount;                                        // Number of times the player has pet Wappy
	uint8_t     messageCount;                                    // Number of times the player has sent any message to Wappy in home mode
	uint8_t     playCount;                                       // Number of times the player has played with Wappy with any toy
	uint8_t     trickCount[TRICK_MAX];                           // Number of times Wappy has randomly performed each trick, see WDTrick
	uint8_t     _unkB2[6];                                       //<! not accessed? Padding?
} WDSave;

// Set up a save file as a newly created one
void WD_CreateNewSave(WDSave* dst);

// Import save file from file name
WDSaveStatus WD_ImportSaveFile(WDSave* dst, const char* savfile_src);

// Save save file to file name
WDSaveStatus WD_ExportSaveFile(const char* savfile_dst, const WDSave* src);

// Import raw data file from file name
WDSaveStatus WD_ImportDataFile(WDSave* dst, const char* binfile_src);

// Save raw data file to file name
WDSaveStatus WD_ExportDataFile(const char* binfile_dst, const WDSave* src);

// Get the value of a game flag
static inline bool WD_GetFlag(WDSave* sav, WDGameFlag flag) {
	return (sav->gameFlags[flag >> 5] & (1 << (flag & 31))) != 0;
}

// Set the value of a game flag
static inline void WD_SetFlag(WDSave* sav, WDGameFlag flag, bool set) {
	uint32_t bit = 1 << (flag & 31);
	if (set) {
		sav->gameFlags[flag >> 5] |= bit;
	} else {
		sav->gameFlags[flag >> 5] &= ~bit;
	}
}

// Turn an unlock flag (eg FLAG_TRICK_CLAP) into the corresponding seen flag for that unlock (FLAG_SEEN_TRICK_CLAP)
// If the flag does not have a seen flag, FLAG_MAX is returned
static inline WDGameFlag WD_SeenFlagFor(WDGameFlag unlock) {
	if (unlock >= FLAG_TOY_START && unlock < FLAG_TRICK_MAX) {
		return (WDGameFlag)(unlock + (FLAG_SEEN_TOY_START - FLAG_TOY_START));
	} else if (unlock >= FLAG_TRAVEL_GAME_EASY_START && unlock < FLAG_HOME_GAME_HARD_MAX) {
		return (WDGameFlag)(unlock + (FLAG_SEEN_TRAVEL_GAME_EASY_START - FLAG_TRAVEL_GAME_EASY_START));
	} else {
		return FLAG_MAX;
	}
}

// Get the current personality of the dog based on the personality scores
static inline WDPersonality WD_CurrentDogPersonality(WDSave* sav) {
	int high_val = -1;
	int high_idx = 0;
	for (int i = PERSONALITY_START; i < PERSONALITY_MAX; i++) {
		if (sav->dogPersonality[i] > high_val) {
			high_val = sav->dogPersonality[i];
			high_idx = i;
		}
	}
	
	return (WDPersonality)high_idx;
}

// Convert the current play time into hours/minutes/seconds
static inline void WD_CalcPlayTime(WDSave* sav, int* out_hours, int* out_minutes, int* out_seconds) {
	int seconds = sav->playTime / 30;
	int minutes = seconds / 60;
	int hours = minutes / 60;
	
	*out_hours = hours;
	*out_minutes = minutes % 60;
	*out_seconds = seconds % 60;
}

#ifdef __cplusplus
}
#endif

#endif
