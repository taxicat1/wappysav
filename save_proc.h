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
	uint32_t    gameFlags[FLAG_NUM_U32S];                        // See WDGameFlag, WD_GetFlag(), WD_SetFlag()
	uint16_t    nickname[NICKNAME_BUF_LEN];                      // 10 wchars + null terminator
	uint8_t     musicVolume;                                     // 0-127
	uint8_t     soundVolume;                                     // 0-127
	uint8_t     travelModeColor;                                 // Enum 0-5, see WDColor
	uint8_t     travelModeAccessory;                             // Enum 0-18, see WDAccessory
	uint8_t     travelModeRoom;                                  // Enum 0-4, see WDRoom
	uint8_t     age;                                             // 1-10 (years)
	int16_t     mood;                                            // -128-127
	uint8_t     personality[PERSONALITY_MAX];                    // Scores 0-255 for each personality type, see WDPersonality, WD_CurrentPersonality()
	uint16_t    friendship;                                      // 0-54999
	uint8_t     fieldshipLevel;                                  // 0-10, updated between screens, set equal to friendship / 5000
	uint8_t     pad4D;                                           // Apparently structure padding (always 0x00)
	uint16_t    fullness;                                        // 0-255, drains over time, feeding increases
	uint16_t    cleanliness;                                     // 0-255, drains over time, grooming increases
	uint8_t     pad52[2];                                        // Apparently structure padding (always 0x00s)
	uint32_t    playTime;                                        // Measured in frames @ 30 fps, max 268435456 (0x10000000), see WD_CalcPlayTime
	uint16_t    minigameScores[MINIGAME_MAX][DIFFICULTY_MAX];    // [game][difficulty], see WDMinigame / WDMinigameDifficulty
	uint8_t     messageReceivedCount;                            // Number of times a message was received from the Wappy robot (max 255)
	uint8_t     minigameWinCount;                                // Number of times the player has won any minigame (max 255)
	uint8_t     fullyCleanedCount;                               // Number of times the player has fully cleaned Wappy (max 255)
	uint8_t     fedCount;                                        // Number of times the player has fed Wappy with any food (max 255)
	uint8_t     minigamePlayCount;                               // Number of times the player has played any minigame (max 255)
	uint8_t     petCount;                                        // Number of times the player has pet Wappy (max 255)
	uint8_t     messageSentCount;                                // Number of times the player has sent any message to Wappy in home mode (max 255)
	uint8_t     toyPlayCount;                                    // Number of times the player has played with Wappy with any toy (max 255)
	uint8_t     trickCount[TRICK_MAX];                           // Number of times Wappy has randomly performed each trick (max 255), see WDTrick
	uint8_t     padB2[6];                                        // Apparently structure padding (always 0x00s)
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

// Turn a seen flag for an unlock (eg FLAG_SEEN_TRICK_CLAP) into the flag for that unlock (FLAG_TRICK_CLAP)
// If the flag is not a seen flag, FLAG_MAX is returned
static inline WDGameFlag WD_UnlockFlagFor(WDGameFlag seen_flag) {
	if (seen_flag >= FLAG_SEEN_TOY_START && seen_flag < FLAG_SEEN_TRICK_MAX) {
		return (WDGameFlag)(seen_flag - (FLAG_SEEN_TOY_START - FLAG_TOY_START));
	} else if (seen_flag >= FLAG_SEEN_TRAVEL_GAME_EASY_START && seen_flag < FLAG_SEEN_HOME_GAME_HARD_MAX) {
		return (WDGameFlag)(seen_flag - (FLAG_SEEN_TRAVEL_GAME_EASY_START - FLAG_TRAVEL_GAME_EASY_START));
	} else {
		return FLAG_MAX;
	}
}

// Get the current personality of the dog based on the personality scores
static inline WDPersonality WD_CurrentPersonality(WDSave* sav) {
	int high_val = -1;
	int high_idx = 0;
	for (int i = PERSONALITY_START; i < PERSONALITY_MAX; i++) {
		if (sav->personality[i] > high_val) {
			high_val = sav->personality[i];
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
