#ifndef WD_DEF_H
#define WD_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	SAVE_STATUS_OK,
	SAVE_STATUS_SIGNATURE_MISMATCH,
	SAVE_STATUS_CHECKSUM_MISMATCH,
	SAVE_STATUS_FILE_FAILURE
} WDSaveStatus;

#define NICKNAME_BUF_LEN (11)

typedef enum {
	FLAG_START = 0,
	
	// General
	FLAG_GENERAL_START = 0,
	FLAG_ENTERED_NICKNAME = 0,                             // 0
	FLAG_HAVE_WAPPYS_HEART,                                // 1
	FLAG_GENERAL_MAX,
	
	// Unlocked rooms
	FLAG_ROOM_START = 2,
	FLAG_ROOM_LIVING_ROOM = 2,                             // 2
	FLAG_ROOM_GARDEN,                                      // 3
	FLAG_ROOM_BEDROOM,                                     // 4
	FLAG_ROOM_KITCHEN,                                     // 5
	FLAG_ROOM_ROOFTOP,                                     // 6
	FLAG_ROOM_MAX,
	
	// Unlocked home games
	FLAG_HOME_GAME_START = 7,
	FLAG_HOME_GAME_FRUIT_CATCH = 7,                        // 7
	FLAG_HOME_GAME_GET_THE_CRITTERS,                       // 8
	FLAG_HOME_GAME_PENGUIN_RUN,                            // 9
	FLAG_HOME_GAME_TARGET_PRACTICE,                        // 10
	FLAG_HOME_GAME_WHERES_THE_FOOD,                        // 11
	FLAG_HOME_GAME_MAX,
	
	// Unlocked travel games
	FLAG_TRAVEL_GAME_START = 12,
	FLAG_TRAVEL_GAME_FRUIT_CATCH = 12,                     // 12
	FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY,                   // 13
	FLAG_TRAVEL_GAME_WAPPYS_RACE,                          // 14
	FLAG_TRAVEL_GAME_PIRATE_BATTLE,                        // 15
	FLAG_TRAVEL_GAME_FIND_THE_FOOD,                        // 16
	FLAG_TRAVEL_GAME_MAX,
	
	// Unlocked toys
	FLAG_ITEM_START = 17,
	
	FLAG_TOY_START = 17,
	FLAG_TOY_BUBBLES = 17,                                 // 17
	FLAG_TOY_BEACH_BALL,                                   // 18
	FLAG_TOY_DISC,                                         // 19
	FLAG_TOY_PAPER_AIRPLANE,                               // 20
	FLAG_TOY_TAMBOURINE,                                   // 21
	FLAG_TOY_MINIATURE_CAR,                                // 22
	FLAG_TOY_FLYING_RING,                                  // 23
	FLAG_TOY_TRUMPET,                                      // 24
	FLAG_TOY_AIRPLANE,                                     // 25
	FLAG_TOY_PENGUIN,                                      // 26
	FLAG_TOY_HELICOPTER,                                   // 27
	FLAG_TOY_TRAMPOLINE,                                   // 28
	FLAG_TOY_DIE,                                          // 29
	FLAG_TOY_UFO,                                          // 30
	FLAG_TOY_MAX,
	
	// Unlocked foods
	FLAG_FOOD_START = 31,
	FLAG_FOOD_SHORTCAKE = 31,                              // 31
	FLAG_FOOD_ORANGE_CAKE,                                 // 32
	FLAG_FOOD_LIME_CAKE,                                   // 33
	FLAG_FOOD_STRW_ECLAIR,                                 // 34
	FLAG_FOOD_CARAMEL_ECLAIR,                              // 35
	FLAG_FOOD_ANGEL_ECLAIR,                                // 36
	FLAG_FOOD_CREAM_PUFF,                                  // 37
	FLAG_FOOD_STRW_CREAM_PUFF,                             // 38
	FLAG_FOOD_KIWI_CREAM_PUFF,                             // 39
	FLAG_FOOD_JELLY_ROLL,                                  // 40
	FLAG_FOOD_STRAWBERRY_ROLL,                             // 41
	FLAG_FOOD_FRUIT_ROLL,                                  // 42
	FLAG_FOOD_BEEF,                                        // 43
	FLAG_FOOD_PORK,                                        // 44
	FLAG_FOOD_CHICKEN,                                     // 45
	FLAG_FOOD_VAN_ICE_CREAM,                               // 46
	FLAG_FOOD_MINT_ICE_CREAM,                              // 47
	FLAG_FOOD_STRW_ICE_CREAM,                              // 48
	FLAG_FOOD_MAX,
	
	FLAG_ITEM_MAX = FLAG_FOOD_MAX,
	
	// Unlocked home mode commands
	FLAG_CMD_START = 49,
	FLAG_CMD_HELLO = 49,                                   // 49
	FLAG_CMD_CALL,                                         // 50
	FLAG_CMD_IM_BACK,                                      // 51
	FLAG_CMD_GOODNIGHT,                                    // 52
	FLAG_CMD_LETS_PLAY,                                    // 53
	FLAG_CMD_BYE,                                          // 54
	FLAG_CMD_DO_SOMETHING,                                 // 55
	FLAG_CMD_WHAT_TO_EAT,                                  // 56
	FLAG_CMD_WHAT_TO_PLAY,                                 // 57
	FLAG_CMD_WHAT_IS_IT,                                   // 58
	FLAG_CMD_ARE_YOU_HUNGRY,                               // 59
	FLAG_CMD_WHAT_TIME_IS_IT,                              // 60
	FLAG_CMD_GOOD_DOG,                                     // 61
	FLAG_CMD_FORTUNE,                                      // 62
	FLAG_CMD_BOO,                                          // 63
	FLAG_CMD_I_LOVE_YOU,                                   // 64
	FLAG_CMD_DO_A_DANCE,                                   // 65
	FLAG_CMD_SING_A_SONG,                                  // 66
	FLAG_CMD_SHORTCAKE,                                    // 67
	FLAG_CMD_ECLAIR,                                       // 68
	FLAG_CMD_CREAM_PUFF,                                   // 69
	FLAG_CMD_JELLY_ROLL,                                   // 70
	FLAG_CMD_DOG_FOOD,                                     // 71
	FLAG_CMD_ICE_CREAM,                                    // 72
	FLAG_CMD_ROCK_PAPER_SCISSORS,                          // 73
	FLAG_CMD_MAX,
	
	// Unlocked colors
	FLAG_COLOR_START = 74,
	FLAG_COLOR_SKY_BLUE = 74,                              // 74
	FLAG_COLOR_GREEN,                                      // 75
	FLAG_COLOR_RED,                                        // 76
	FLAG_COLOR_PINK,                                       // 77
	FLAG_COLOR_PURPLE,                                     // 78
	FLAG_COLOR_GOLD,                                       // 79
	FLAG_COLOR_MAX,
	
	// Unlocked ear accessories
	FLAG_ACCESSORY_START = 80,
	FLAG_ACCESSORY_WAPPY_BADGE_1 = 80,                     // 80
	FLAG_ACCESSORY_WAPPY_BADGE_2,                          // 81
	FLAG_ACCESSORY_WAPPY_BADGE_3,                          // 82
	FLAG_ACCESSORY_STAR_1,                                 // 83
	FLAG_ACCESSORY_STAR_2,                                 // 84
	FLAG_ACCESSORY_STAR_3,                                 // 85
	FLAG_ACCESSORY_HEART_1,                                // 86
	FLAG_ACCESSORY_HEART_2,                                // 87
	FLAG_ACCESSORY_HEART_3,                                // 88
	FLAG_ACCESSORY_FLOWER_1,                               // 89
	FLAG_ACCESSORY_FLOWER_2,                               // 90
	FLAG_ACCESSORY_FLOWER_3,                               // 91
	FLAG_ACCESSORY_RIBBON_1,                               // 92
	FLAG_ACCESSORY_RIBBON_2,                               // 93
	FLAG_ACCESSORY_RIBBON_3,                               // 94
	FLAG_ACCESSORY_BUTTERFLY_1,                            // 95
	FLAG_ACCESSORY_BUTTERFLY_2,                            // 96
	FLAG_ACCESSORY_BUTTERFLY_3,                            // 97
	FLAG_ACCESSORY_MAX,
	
	// Unlocked tricks
	FLAG_TRICK_START = 98,
	FLAG_TRICK_SHAKE = 98,                                 // 98
	FLAG_TRICK_STRETCH,                                    // 99
	FLAG_TRICK_GROOMING,                                   // 100
	FLAG_TRICK_STAND,                                      // 101
	FLAG_TRICK_HANDSTAND,                                  // 102
	FLAG_TRICK_BACKFLIP,                                   // 103
	FLAG_TRICK_HAPPY_DANCE,                                // 104
	FLAG_TRICK_SHOW_OFF,                                   // 105
	FLAG_TRICK_FRONT_FLIP,                                 // 106
	FLAG_TRICK_DOUBLE_FRONT_FLIP,                          // 107
	FLAG_TRICK_TRIPLE_FRONT_FLIP,                          // 108
	FLAG_TRICK_ROLL_OVER,                                  // 109
	FLAG_TRICK_SNOW_ANGEL,                                 // 110
	FLAG_TRICK_CLAP,                                       // 111
	FLAG_TRICK_MONKEY_DANCE,                               // 112
	FLAG_TRICK_JUMP_AND_FLIP,                              // 113
	FLAG_TRICK_BODY_SHAKE,                                 // 114
	FLAG_TRICK_HULA,                                       // 115
	FLAG_TRICK_DIZZY,                                      // 116
	FLAG_TRICK_STAND_ON_ONE_LEG,                           // 117
	FLAG_TRICK_SUPER_HANDSTAND,                            // 118
	FLAG_TRICK_BREAKDANCE,                                 // 119
	FLAG_TRICK_MAX,
	
	// Seemingly unused flags. Not changed between new save and 100% save
	// 120, 125, and 130 are set to 1 during new save creation
	FLAG_UNUSED_START = 120,
	FLAG_UNUSED_120 = 120,                                 // 120
	FLAG_UNUSED_121,                                       // 121
	FLAG_UNUSED_122,                                       // 122
	FLAG_UNUSED_123,                                       // 123
	FLAG_UNUSED_124,                                       // 124
	FLAG_UNUSED_125,                                       // 125
	FLAG_UNUSED_126,                                       // 126
	FLAG_UNUSED_127,                                       // 127
	FLAG_UNUSED_128,                                       // 128
	FLAG_UNUSED_129,                                       // 129
	FLAG_UNUSED_130,                                       // 130
	FLAG_UNUSED_131,                                       // 131
	FLAG_UNUSED_132,                                       // 132
	FLAG_UNUSED_133,                                       // 133
	FLAG_UNUSED_134,                                       // 134
	FLAG_UNUSED_MAX,
	
	// 'New!' flag for unlocked toys
	FLAG_SEEN_ITEM_START = 135,
	
	FLAG_SEEN_TOY_START = 135,
	FLAG_SEEN_TOY_BUBBLES = 135,                           // 135
	FLAG_SEEN_TOY_BEACH_BALL,                              // 136
	FLAG_SEEN_TOY_DISC,                                    // 137
	FLAG_SEEN_TOY_PAPER_AIRPLANE,                          // 138
	FLAG_SEEN_TOY_TAMBOURINE,                              // 139
	FLAG_SEEN_TOY_MINIATURE_CAR,                           // 140
	FLAG_SEEN_TOY_FLYING_RING,                             // 141
	FLAG_SEEN_TOY_TRUMPET,                                 // 142
	FLAG_SEEN_TOY_AIRPLANE,                                // 143
	FLAG_SEEN_TOY_PENGUIN,                                 // 144
	FLAG_SEEN_TOY_HELICOPTER,                              // 145
	FLAG_SEEN_TOY_TRAMPOLINE,                              // 146
	FLAG_SEEN_TOY_DIE,                                     // 147
	FLAG_SEEN_TOY_UFO,                                     // 148
	FLAG_SEEN_TOY_MAX,
	
	// 'New!' flag for unlocked foods
	FLAG_SEEN_FOOD_START = 149,
	FLAG_SEEN_FOOD_SHORTCAKE = 149,                        // 149
	FLAG_SEEN_FOOD_ORANGE_CAKE,                            // 150
	FLAG_SEEN_FOOD_LIME_CAKE,                              // 151
	FLAG_SEEN_FOOD_STRW_ECLAIR,                            // 152
	FLAG_SEEN_FOOD_CARAMEL_ECLAIR,                         // 153
	FLAG_SEEN_FOOD_ANGEL_ECLAIR,                           // 154
	FLAG_SEEN_FOOD_CREAM_PUFF,                             // 155
	FLAG_SEEN_FOOD_STRW_CREAM_PUFF,                        // 156
	FLAG_SEEN_FOOD_KIWI_CREAM_PUFF,                        // 157
	FLAG_SEEN_FOOD_JELLY_ROLL,                             // 158
	FLAG_SEEN_FOOD_STRAWBERRY_ROLL,                        // 159
	FLAG_SEEN_FOOD_FRUIT_ROLL,                             // 160
	FLAG_SEEN_FOOD_BEEF,                                   // 161
	FLAG_SEEN_FOOD_PORK,                                   // 162
	FLAG_SEEN_FOOD_CHICKEN,                                // 163
	FLAG_SEEN_FOOD_VAN_ICE_CREAM,                          // 164
	FLAG_SEEN_FOOD_MINT_ICE_CREAM,                         // 165
	FLAG_SEEN_FOOD_STRW_ICE_CREAM,                         // 166
	FLAG_SEEN_FOOD_MAX,
	
	FLAG_SEEN_ITEM_MAX = FLAG_SEEN_FOOD_MAX,
	
	// 'New!' flag for unlocked commands
	FLAG_SEEN_CMD_START = 167,
	FLAG_SEEN_CMD_HELLO = 167,                             // 167
	FLAG_SEEN_CMD_CALL,                                    // 168
	FLAG_SEEN_CMD_IM_BACK,                                 // 169
	FLAG_SEEN_CMD_GOODNIGHT,                               // 170
	FLAG_SEEN_CMD_LETS_PLAY,                               // 171
	FLAG_SEEN_CMD_BYE,                                     // 172
	FLAG_SEEN_CMD_DO_SOMETHING,                            // 173
	FLAG_SEEN_CMD_WHAT_TO_EAT,                             // 174
	FLAG_SEEN_CMD_WHAT_TO_PLAY,                            // 175
	FLAG_SEEN_CMD_WHAT_IS_IT,                              // 176
	FLAG_SEEN_CMD_ARE_YOU_HUNGRY,                          // 177
	FLAG_SEEN_CMD_WHAT_TIME_IS_IT,                         // 178
	FLAG_SEEN_CMD_GOOD_DOG,                                // 179
	FLAG_SEEN_CMD_FORTUNE,                                 // 180
	FLAG_SEEN_CMD_BOO,                                     // 181
	FLAG_SEEN_CMD_I_LOVE_YOU,                              // 182
	FLAG_SEEN_CMD_DO_A_DANCE,                              // 183
	FLAG_SEEN_CMD_SING_A_SONG,                             // 184
	FLAG_SEEN_CMD_SHORTCAKE,                               // 185
	FLAG_SEEN_CMD_ECLAIR,                                  // 186
	FLAG_SEEN_CMD_CREAM_PUFF,                              // 187
	FLAG_SEEN_CMD_JELLY_ROLL,                              // 188
	FLAG_SEEN_CMD_DOG_FOOD,                                // 189
	FLAG_SEEN_CMD_ICE_CREAM,                               // 190
	FLAG_SEEN_CMD_ROCK_PAPER_SCISSORS,                     // 191
	FLAG_SEEN_CMD_MAX,
	
	// 'New!' flag for unlocked colors
	FLAG_SEEN_COLOR_START = 192,
	FLAG_SEEN_COLOR_SKY_BLUE = 192,                        // 192
	FLAG_SEEN_COLOR_GREEN,                                 // 193
	FLAG_SEEN_COLOR_RED,                                   // 194
	FLAG_SEEN_COLOR_PINK,                                  // 195
	FLAG_SEEN_COLOR_PURPLE,                                // 196
	FLAG_SEEN_COLOR_GOLD,                                  // 197
	FLAG_SEEN_COLOR_MAX,
	
	// 'New!' flag for unlocked accessories
	FLAG_SEEN_ACCESSORY_START = 198,
	FLAG_SEEN_ACCESSORY_WAPPY_BADGE_1 = 198,               // 198
	FLAG_SEEN_ACCESSORY_WAPPY_BADGE_2,                     // 199
	FLAG_SEEN_ACCESSORY_WAPPY_BADGE_3,                     // 200
	FLAG_SEEN_ACCESSORY_STAR_1,                            // 201
	FLAG_SEEN_ACCESSORY_STAR_2,                            // 202
	FLAG_SEEN_ACCESSORY_STAR_3,                            // 203
	FLAG_SEEN_ACCESSORY_HEART_1,                           // 204
	FLAG_SEEN_ACCESSORY_HEART_2,                           // 205
	FLAG_SEEN_ACCESSORY_HEART_3,                           // 206
	FLAG_SEEN_ACCESSORY_FLOWER_1,                          // 207
	FLAG_SEEN_ACCESSORY_FLOWER_2,                          // 208
	FLAG_SEEN_ACCESSORY_FLOWER_3,                          // 209
	FLAG_SEEN_ACCESSORY_RIBBON_1,                          // 210
	FLAG_SEEN_ACCESSORY_RIBBON_2,                          // 211
	FLAG_SEEN_ACCESSORY_RIBBON_3,                          // 212
	FLAG_SEEN_ACCESSORY_BUTTERFLY_1,                       // 213
	FLAG_SEEN_ACCESSORY_BUTTERFLY_2,                       // 214
	FLAG_SEEN_ACCESSORY_BUTTERFLY_3,                       // 215
	FLAG_SEEN_ACCESSORY_MAX,
	
	// 'New!' flag for unlocked tricks
	FLAG_SEEN_TRICK_START = 216,
	FLAG_SEEN_TRICK_SHAKE = 216,                           // 216
	FLAG_SEEN_TRICK_STRETCH,                               // 217
	FLAG_SEEN_TRICK_GROOMING,                              // 218
	FLAG_SEEN_TRICK_STAND,                                 // 219
	FLAG_SEEN_TRICK_HANDSTAND,                             // 220
	FLAG_SEEN_TRICK_BACKFLIP,                              // 221
	FLAG_SEEN_TRICK_HAPPY_DANCE,                           // 222
	FLAG_SEEN_TRICK_SHOW_OFF,                              // 223
	FLAG_SEEN_TRICK_FRONT_FLIP,                            // 224
	FLAG_SEEN_TRICK_DOUBLE_FRONT_FLIP,                     // 225
	FLAG_SEEN_TRICK_TRIPLE_FRONT_FLIP,                     // 226
	FLAG_SEEN_TRICK_ROLL_OVER,                             // 227
	FLAG_SEEN_TRICK_SNOW_ANGEL,                            // 228
	FLAG_SEEN_TRICK_CLAP,                                  // 229
	FLAG_SEEN_TRICK_MONKEY_DANCE,                          // 230
	FLAG_SEEN_TRICK_JUMP_AND_FLIP,                         // 231
	FLAG_SEEN_TRICK_BODY_SHAKE,                            // 232
	FLAG_SEEN_TRICK_HULA,                                  // 233
	FLAG_SEEN_TRICK_DIZZY,                                 // 234
	FLAG_SEEN_TRICK_STAND_ON_ONE_LEG,                      // 235
	FLAG_SEEN_TRICK_SUPER_HANDSTAND,                       // 236
	FLAG_SEEN_TRICK_BREAKDANCE,                            // 237
	FLAG_SEEN_TRICK_MAX,
	
	// Unlocked easy difficulties for travel games
	FLAG_GAME_DIFFICULTY_START = 238,
	
	FLAG_GAME_EASY_START = 238,
	
	FLAG_TRAVEL_GAME_EASY_START = 238,
	FLAG_TRAVEL_GAME_FRUIT_CATCH_EASY = 238,               // 238
	FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_EASY,              // 239
	FLAG_TRAVEL_GAME_WAPPYS_RACE_EASY,                     // 240
	FLAG_TRAVEL_GAME_PIRATE_BATTLE_EASY,                   // 241
	FLAG_TRAVEL_GAME_FIND_THE_FOOD_EASY,                   // 242
	FLAG_TRAVEL_GAME_EASY_MAX,
	
	// Unlocked easy difficulties for home games
	FLAG_HOME_GAME_EASY_START = 243,
	FLAG_HOME_GAME_FRUIT_CATCH_EASY = 243,                 // 243
	FLAG_HOME_GAME_GET_THE_CRITTERS_EASY,                  // 244
	FLAG_HOME_GAME_PENGUIN_RUN_EASY,                       // 245
	FLAG_HOME_GAME_TARGET_PRACTICE_EASY,                   // 246
	FLAG_HOME_GAME_WHERES_THE_FOOD_EASY,                   // 247
	FLAG_HOME_GAME_EASY_MAX,
	
	FLAG_GAME_EASY_MAX = FLAG_HOME_GAME_EASY_MAX,
	
	// Unlocked normal difficulties for travel games
	FLAG_GAME_NORMAL_START = 248,
	
	FLAG_TRAVEL_GAME_NORMAL_START = 248,
	FLAG_TRAVEL_GAME_FRUIT_CATCH_NORMAL = 248,             // 248
	FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_NORMAL,            // 249
	FLAG_TRAVEL_GAME_WAPPYS_RACE_NORMAL,                   // 250
	FLAG_TRAVEL_GAME_PIRATE_BATTLE_NORMAL,                 // 251
	FLAG_TRAVEL_GAME_FIND_THE_FOOD_NORMAL,                 // 252
	FLAG_TRAVEL_GAME_NORMAL_MAX,
	
	// Unlocked normal difficulties for home games
	FLAG_HOME_GAME_NORMAL_START = 253,
	FLAG_HOME_GAME_FRUIT_CATCH_NORMAL = 253,               // 253
	FLAG_HOME_GAME_GET_THE_CRITTERS_NORMAL,                // 254
	FLAG_HOME_GAME_PENGUIN_RUN_NORMAL,                     // 255
	FLAG_HOME_GAME_TARGET_PRACTICE_NORMAL,                 // 256
	FLAG_HOME_GAME_WHERES_THE_FOOD_NORMAL,                 // 257
	FLAG_HOME_GAME_NORMAL_MAX,
	
	FLAG_GAME_NORMAL_MAX = FLAG_HOME_GAME_NORMAL_MAX,
	
	// Unlocked hard difficulties for travel games
	FLAG_GAME_HARD_START = 258,
	
	FLAG_TRAVEL_GAME_HARD_START = 258,
	FLAG_TRAVEL_GAME_FRUIT_CATCH_HARD = 258,               // 258
	FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_HARD,              // 259
	FLAG_TRAVEL_GAME_WAPPYS_RACE_HARD,                     // 260
	FLAG_TRAVEL_GAME_PIRATE_BATTLE_HARD,                   // 261
	FLAG_TRAVEL_GAME_FIND_THE_FOOD_HARD,                   // 262
	FLAG_TRAVEL_GAME_HARD_MAX,
	
	// Unlocked hard difficulties for home games
	FLAG_HOME_GAME_HARD_START = 263,
	FLAG_HOME_GAME_FRUIT_CATCH_HARD = 263,                 // 263
	FLAG_HOME_GAME_GET_THE_CRITTERS_HARD,                  // 264
	FLAG_HOME_GAME_PENGUIN_RUN_HARD,                       // 265
	FLAG_HOME_GAME_TARGET_PRACTICE_HARD,                   // 266
	FLAG_HOME_GAME_WHERES_THE_FOOD_HARD,                   // 267
	FLAG_HOME_GAME_HARD_MAX,
	
	FLAG_GAME_HARD_MAX = FLAG_HOME_GAME_HARD_MAX,
	
	FLAG_GAME_DIFFICULTY_MAX = FLAG_GAME_HARD_MAX,
	
	// "New!" flag for unlocked easy difficulties for travel games
	FLAG_SEEN_GAME_DIFFICULTY_START = 268,
	
	FLAG_SEEN_GAME_EASY_START = 268,
	
	FLAG_SEEN_TRAVEL_GAME_EASY_START = 268,
	FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_EASY = 268,          // 268
	FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_EASY,         // 269
	FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_EASY,                // 270
	FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_EASY,              // 271
	FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_EASY,              // 272
	FLAG_SEEN_TRAVEL_GAME_EASY_MAX,
	
	// "New!" flag for unlocked easy difficulties for home games
	FLAG_SEEN_HOME_GAME_EASY_START = 273,
	FLAG_SEEN_HOME_GAME_FRUIT_CATCH_EASY = 273,            // 273
	FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_EASY,             // 274
	FLAG_SEEN_HOME_GAME_PENGUIN_RUN_EASY,                  // 275
	FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_EASY,              // 276
	FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_EASY,              // 277
	FLAG_SEEN_HOME_GAME_EASY_MAX,
	
	FLAG_SEEN_GAME_EASY_MAX = FLAG_SEEN_HOME_GAME_EASY_MAX,
	
	// "New!" flag for unlocked normal difficulties for travel games
	FLAG_SEEN_GAME_NORMAL_START = 278,
	
	FLAG_SEEN_TRAVEL_GAME_NORMAL_START = 278,
	FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_NORMAL = 278,        // 278
	FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_NORMAL,       // 279
	FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_NORMAL,              // 280
	FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_NORMAL,            // 281
	FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_NORMAL,            // 282
	FLAG_SEEN_TRAVEL_GAME_NORMAL_MAX,
	
	// "New!" flag for unlocked normal difficulties for home games
	FLAG_SEEN_HOME_GAME_NORMAL_START = 283,
	FLAG_SEEN_HOME_GAME_FRUIT_CATCH_NORMAL = 283,          // 283
	FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_NORMAL,           // 284
	FLAG_SEEN_HOME_GAME_PENGUIN_RUN_NORMAL,                // 285
	FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_NORMAL,            // 286
	FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_NORMAL,            // 287
	FLAG_SEEN_HOME_GAME_NORMAL_MAX,
	
	FLAG_SEEN_GAME_NORMAL_MAX = FLAG_SEEN_HOME_GAME_NORMAL_MAX,
	
	// "New!" flag for unlocked hard difficulties for travel games
	FLAG_SEEN_GAME_HARD_START = 288,
	
	FLAG_SEEN_TRAVEL_GAME_HARD_START = 288,
	FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_HARD = 288,          // 288
	FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_HARD,         // 289
	FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_HARD,                // 290
	FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_HARD,              // 291
	FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_HARD,              // 292
	FLAG_SEEN_TRAVEL_GAME_HARD_MAX,
	
	// "New!" flag for unlocked hard difficulties for home games
	FLAG_SEEN_HOME_GAME_HARD_START = 293,
	FLAG_SEEN_HOME_GAME_FRUIT_CATCH_HARD = 293,            // 293
	FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_HARD,             // 294
	FLAG_SEEN_HOME_GAME_PENGUIN_RUN_HARD,                  // 295
	FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_HARD,              // 296
	FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_HARD,              // 297
	FLAG_SEEN_HOME_GAME_HARD_MAX,
	
	FLAG_SEEN_GAME_HARD_MAX = FLAG_SEEN_HOME_GAME_HARD_MAX,
	
	FLAG_SEEN_GAME_DIFFICULTY_MAX = FLAG_SEEN_GAME_HARD_MAX,
	
	// Flag if viewed message boxes
	FLAG_SEEN_MESSAGE_START = 298,
	FLAG_SEEN_MESSAGE_FOOD = 298,                          // 298
	FLAG_SEEN_MESSAGE_TOYS,                                // 299
	FLAG_SEEN_MESSAGE_CLEANING,                            // 300
	FLAG_SEEN_MESSAGE_INTRO,                               // 301
	FLAG_SEEN_MESSAGE_MAX,
	
	// Unused flags (set to 0 in new save file)
	FLAG_FOOTER_START = 302,
	FLAG_UNUSED_302 = 302,                                 // 302
	FLAG_UNUSED_303,                                       // 303
	FLAG_UNUSED_304,                                       // 304
	FLAG_UNUSED_305,                                       // 305
	FLAG_UNUSED_306,                                       // 306
	FLAG_UNUSED_307,                                       // 307
	FLAG_UNUSED_308,                                       // 308
	FLAG_UNUSED_309,                                       // 309
	FLAG_UNUSED_310,                                       // 310
	FLAG_UNUSED_311,                                       // 311
	FLAG_UNUSED_312,                                       // 312
	FLAG_UNUSED_313,                                       // 313
	FLAG_UNUSED_314,                                       // 314
	FLAG_UNUSED_315,                                       // 315
	FLAG_UNUSED_316,                                       // 316
	FLAG_UNUSED_317,                                       // 317
	FLAG_UNUSED_318,                                       // 318
	FLAG_UNUSED_319,                                       // 319
	FLAG_FOOTER_MAX,
	
	FLAG_MAX = FLAG_FOOTER_MAX
} WDGameFlag;

#define FLAG_NUM_U32S  ((FLAG_MAX + 31) / 32)

static const char* WDGameFlagStr[] = {
	// General
	"Have entered a nickname",                             // FLAG_ENTERED_NICKNAME
	"Have Wappy's heart",                                  // FLAG_HAVE_WAPPYS_HEART
	
	// Unlocked rooms
	"Living Room",                                         // FLAG_ROOM_LIVING_ROOM
	"Garden",                                              // FLAG_ROOM_GARDEN
	"Bedroom",                                             // FLAG_ROOM_BEDROOM
	"Kitchen",                                             // FLAG_ROOM_KITCHEN
	"Rooftop",                                             // FLAG_ROOM_ROOFTOP
	
	// Unlocked home games
	"Fruit Catch",                                         // FLAG_HOME_GAME_FRUIT_CATCH
	"Get the Critters!",                                   // FLAG_HOME_GAME_GET_THE_CRITTERS
	"Penguin Run",                                         // FLAG_HOME_GAME_PENGUIN_RUN
	"Target Practice",                                     // FLAG_HOME_GAME_TARGET_PRACTICE
	"Where's the Food?",                                   // FLAG_HOME_GAME_WHERES_THE_FOOD
	
	// Unlocked travel games
	"Fruit Catch",                                         // FLAG_TRAVEL_GAME_FRUIT_CATCH
	"Which one is Wappy?",                                 // FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY
	"Wappy's Race",                                        // FLAG_TRAVEL_GAME_WAPPYS_RACE
	"Pirate Battle",                                       // FLAG_TRAVEL_GAME_PIRATE_BATTLE
	"Find the Food!",                                      // FLAG_TRAVEL_GAME_FIND_THE_FOOD
	
	// Unlocked toys
	"Bubbles",                                             // FLAG_TOY_BUBBLES
	"Beach ball",                                          // FLAG_TOY_BEACH_BALL
	"Disc",                                                // FLAG_TOY_DISC
	"Paper airplane",                                      // FLAG_TOY_PAPER_AIRPLANE
	"Tambourine",                                          // FLAG_TOY_TAMBOURINE
	"Miniature car",                                       // FLAG_TOY_MINIATURE_CAR
	"Flying ring",                                         // FLAG_TOY_FLYING_RING
	"Trumpet",                                             // FLAG_TOY_TRUMPET
	"Airplane",                                            // FLAG_TOY_AIRPLANE
	"Penguin",                                             // FLAG_TOY_PENGUIN
	"Helicopter",                                          // FLAG_TOY_HELICOPTER
	"Trampoline",                                          // FLAG_TOY_TRAMPOLINE
	"Die",                                                 // FLAG_TOY_DIE
	"UFO",                                                 // FLAG_TOY_UFO
	
	// Unlocked foods
	"Shortcake",                                           // FLAG_FOOD_SHORTCAKE
	"Orange Cake",                                         // FLAG_FOOD_ORANGE_CAKE
	"Lime Cake",                                           // FLAG_FOOD_LIME_CAKE
	"Strw. Eclair",                                        // FLAG_FOOD_STRW_ECLAIR
	"Caramel Eclair",                                      // FLAG_FOOD_CARAMEL_ECLAIR
	"Angel Eclair",                                        // FLAG_FOOD_ANGEL_ECLAIR
	"Cream Puff",                                          // FLAG_FOOD_CREAM_PUFF
	"Strw Cream Puff",                                     // FLAG_FOOD_STRW_CREAM_PUFF
	"Kiwi cream puff",                                     // FLAG_FOOD_KIWI_CREAM_PUFF
	"Jelly Roll",                                          // FLAG_FOOD_JELLY_ROLL
	"Strawberry Roll",                                     // FLAG_FOOD_STRAWBERRY_ROLL
	"Fruit Roll",                                          // FLAG_FOOD_FRUIT_ROLL
	"Beef",                                                // FLAG_FOOD_BEEF
	"Pork",                                                // FLAG_FOOD_PORK
	"Chicken",                                             // FLAG_FOOD_CHICKEN
	"Van. Ice Cream",                                      // FLAG_FOOD_VAN_ICE_CREAM
	"Mint Ice Vream",                                      // FLAG_FOOD_MINT_ICE_CREAM
	"Strw. Ice Cream",                                     // FLAG_FOOD_STRW_ICE_CREAM
	
	// Unlocked commands
	"Hello!",                                              // FLAG_CMD_HELLO
	"Call",                                                // FLAG_CMD_CALL
	"I'm back!",                                           // FLAG_CMD_IM_BACK
	"Goodnight!",                                          // FLAG_CMD_GOODNIGHT
	"Let's play!",                                         // FLAG_CMD_LETS_PLAY
	"Bye!",                                                // FLAG_CMD_BYE
	"Do something?",                                       // FLAG_CMD_DO_SOMETHING
	"What to eat?",                                        // FLAG_CMD_WHAT_TO_EAT
	"Let's play!",                                         // FLAG_CMD_WHAT_TO_PLAY
	"What is it?",                                         // FLAG_CMD_WHAT_IS_IT
	"Are you hungry?",                                     // FLAG_CMD_ARE_YOU_HUNGRY
	"What time is it?",                                    // FLAG_CMD_WHAT_TIME_IS_IT
	"Good dog!",                                           // FLAG_CMD_GOOD_DOG
	"Fortune",                                             // FLAG_CMD_FORTUNE
	"Boo!",                                                // FLAG_CMD_BOO
	"I love you!",                                         // FLAG_CMD_I_LOVE_YOU
	"Do a dance!",                                         // FLAG_CMD_DO_A_DANCE
	"Sing a song!",                                        // FLAG_CMD_SING_A_SONG
	"Shortcake",                                           // FLAG_CMD_SHORTCAKE
	"Eclair",                                              // FLAG_CMD_ECLAIR
	"Cream Puff",                                          // FLAG_CMD_CREAM_PUFF
	"Jelly Roll",                                          // FLAG_CMD_JELLY_ROLL
	"Dog Food",                                            // FLAG_CMD_DOG_FOOD
	"Ice Cream",                                           // FLAG_CMD_ICE_CREAM
	"Rock Paper Scissors",                                 // FLAG_CMD_ROCK_PAPER_SCISSORS
	
	// Unlocked colors
	"Sky Blue",                                            // FLAG_COLOR_SKY_BLUE
	"Green",                                               // FLAG_COLOR_GREEN
	"Red",                                                 // FLAG_COLOR_RED
	"Pink",                                                // FLAG_COLOR_PINK
	"Purple",                                              // FLAG_COLOR_PURPLE
	"Gold",                                                // FLAG_COLOR_GOLD
	
	// Unlocked accessories
	"Wappy Badge (blue)",                                  // FLAG_ACCESSORY_WAPPY_BADGE_1
	"Wappy Badge (pink)",                                  // FLAG_ACCESSORY_WAPPY_BADGE_2
	"Wappy Badge (yellow)",                                // FLAG_ACCESSORY_WAPPY_BADGE_3
	"Star (yellow)",                                       // FLAG_ACCESSORY_STAR_1
	"Star (blue)",                                         // FLAG_ACCESSORY_STAR_2
	"Star (red)",                                          // FLAG_ACCESSORY_STAR_3
	"Heart (pink)",                                        // FLAG_ACCESSORY_HEART_1
	"Heart (blue)",                                        // FLAG_ACCESSORY_HEART_2
	"Heart (red)",                                         // FLAG_ACCESSORY_HEART_3
	"Flower (orange)",                                     // FLAG_ACCESSORY_FLOWER_1
	"Flower (purple)",                                     // FLAG_ACCESSORY_FLOWER_2
	"Flower (green)",                                      // FLAG_ACCESSORY_FLOWER_3
	"Ribbon (pink)",                                       // FLAG_ACCESSORY_RIBBON_1
	"Ribbon (green)",                                      // FLAG_ACCESSORY_RIBBON_2
	"Ribbon (yellow)",                                     // FLAG_ACCESSORY_RIBBON_3
	"Butterfly (purple)",                                  // FLAG_ACCESSORY_BUTTERFLY_1
	"Butterfly (blue)",                                    // FLAG_ACCESSORY_BUTTERFLY_2
	"Butterfly (orange)",                                  // FLAG_ACCESSORY_BUTTERFLY_3
	
	// Unlocked tricks
	"Shake",                                               // FLAG_TRICK_SHAKE
	"Stretch",                                             // FLAG_TRICK_STRETCH
	"Grooming",                                            // FLAG_TRICK_GROOMING
	"Stand",                                               // FLAG_TRICK_STAND
	"Handstand",                                           // FLAG_TRICK_HANDSTAND
	"Backflip",                                            // FLAG_TRICK_BACKFLIP
	"Happy Dance",                                         // FLAG_TRICK_HAPPY_DANCE
	"Show Off",                                            // FLAG_TRICK_SHOW_OFF
	"Front Flip",                                          // FLAG_TRICK_FRONT_FLIP
	"Double Front Flip",                                   // FLAG_TRICK_DOUBLE_FRONT_FLIP
	"Triple Front Flip",                                   // FLAG_TRICK_TRIPLE_FRONT_FLIP
	"Roll Over",                                           // FLAG_TRICK_ROLL_OVER
	"Snow Angel",                                          // FLAG_TRICK_SNOW_ANGEL
	"Clap",                                                // FLAG_TRICK_CLAP
	"Monkey Dance",                                        // FLAG_TRICK_MONKEY_DANCE
	"Jump and Flip",                                       // FLAG_TRICK_JUMP_AND_FLIP
	"Body Shake",                                          // FLAG_TRICK_BODY_SHAKE
	"Hula",                                                // FLAG_TRICK_HULA
	"Dizzy",                                               // FLAG_TRICK_DIZZY
	"Stand on One Leg",                                    // FLAG_TRICK_STAND_ON_ONE_LEG
	"Super Handstand!",                                    // FLAG_TRICK_SUPER_HANDSTAND
	"Breakdance!",                                         // FLAG_TRICK_BREAKDANCE
	
	// Seemingly unused flags. Not changed between new save and 100% save
	// 120, 125, and 130 are set to 1 during new save creation
	"Unused (120)",                                        // FLAG_UNUSED_120
	"Unused (121)",                                        // FLAG_UNUSED_121
	"Unused (122)",                                        // FLAG_UNUSED_122
	"Unused (123)",                                        // FLAG_UNUSED_123
	"Unused (124)",                                        // FLAG_UNUSED_124
	"Unused (125)",                                        // FLAG_UNUSED_125
	"Unused (126)",                                        // FLAG_UNUSED_126
	"Unused (127)",                                        // FLAG_UNUSED_127
	"Unused (128)",                                        // FLAG_UNUSED_128
	"Unused (129)",                                        // FLAG_UNUSED_129
	"Unused (130)",                                        // FLAG_UNUSED_130
	"Unused (131)",                                        // FLAG_UNUSED_131
	"Unused (132)",                                        // FLAG_UNUSED_132
	"Unused (133)",                                        // FLAG_UNUSED_133
	"Unused (134)",                                        // FLAG_UNUSED_134
	
	// 'New!' flag for unlocked toys
	"Seen Bubbles",                                        // FLAG_SEEN_TOY_BUBBLES
	"Seen Beach ball",                                     // FLAG_SEEN_TOY_BEACH_BALL
	"Seen Disc",                                           // FLAG_SEEN_TOY_DISC
	"Seen Paper airplane",                                 // FLAG_SEEN_TOY_PAPER_AIRPLANE
	"Seen Tambourine",                                     // FLAG_SEEN_TOY_TAMBOURINE
	"Seen Miniature car",                                  // FLAG_SEEN_TOY_MINIATURE_CAR
	"Seen Flying ring",                                    // FLAG_SEEN_TOY_FLYING_RING
	"Seen Trumpet",                                        // FLAG_SEEN_TOY_TRUMPET
	"Seen Airplane",                                       // FLAG_SEEN_TOY_AIRPLANE
	"Seen Penguin",                                        // FLAG_SEEN_TOY_PENGUIN
	"Seen Helicopter",                                     // FLAG_SEEN_TOY_HELICOPTER
	"Seen Trampoline",                                     // FLAG_SEEN_TOY_TRAMPOLINE
	"Seen Die",                                            // FLAG_SEEN_TOY_DIE
	"Seen UFO",                                            // FLAG_SEEN_TOY_UFO
	
	// 'New!' flag for unlocked foods
	"Seen Shortcake",                                      // FLAG_SEEN_FOOD_SHORTCAKE
	"Seen Orange Cake",                                    // FLAG_SEEN_FOOD_ORANGE_CAKE
	"Seen Lime Cake",                                      // FLAG_SEEN_FOOD_LIME_CAKE
	"Seen Strw. Eclair",                                   // FLAG_SEEN_FOOD_STRW_ECLAIR
	"Seen Caramel Eclair",                                 // FLAG_SEEN_FOOD_CARAMEL_ECLAIR
	"Seen Angel Eclair",                                   // FLAG_SEEN_FOOD_ANGEL_ECLAIR
	"Seen Cream Puff",                                     // FLAG_SEEN_FOOD_CREAM_PUFF
	"Seen Strw Cream Puff",                                // FLAG_SEEN_FOOD_STRW_CREAM_PUFF
	"Seen Kiwi cream puff",                                // FLAG_SEEN_FOOD_KIWI_CREAM_PUFF
	"Seen Jelly Roll",                                     // FLAG_SEEN_FOOD_JELLY_ROLL
	"Seen Strawberry Roll",                                // FLAG_SEEN_FOOD_STRAWBERRY_ROLL
	"Seen Fruit Roll",                                     // FLAG_SEEN_FOOD_FRUIT_ROLL
	"Seen Beef",                                           // FLAG_SEEN_FOOD_BEEF
	"Seen Pork",                                           // FLAG_SEEN_FOOD_PORK
	"Seen Chicken",                                        // FLAG_SEEN_FOOD_CHICKEN
	"Seen Van. Ice Cream",                                 // FLAG_SEEN_FOOD_VAN_ICE_CREAM
	"Seen Mint Ice Vream",                                 // FLAG_SEEN_FOOD_MINT_ICE_CREAM
	"Seen Strw. Ice Cream",                                // FLAG_SEEN_FOOD_STRW_ICE_CREAM
	
	// 'New!' flag for unlocked commands
	"Seen Hello!",                                         // FLAG_SEEN_CMD_HELLO
	"Seen Call",                                           // FLAG_SEEN_CMD_CALL
	"Seen I'm back!",                                      // FLAG_SEEN_CMD_IM_BACK
	"Seen Goodnight!",                                     // FLAG_SEEN_CMD_GOODNIGHT
	"Seen Let's play!",                                    // FLAG_SEEN_CMD_LETS_PLAY
	"Seen Bye!",                                           // FLAG_SEEN_CMD_BYE
	"Seen Do something?",                                  // FLAG_SEEN_CMD_DO_SOMETHING
	"Seen What to eat?",                                   // FLAG_SEEN_CMD_WHAT_TO_EAT
	"Seen Let's play!",                                    // FLAG_SEEN_CMD_WHAT_TO_PLAY
	"Seen What is it?",                                    // FLAG_SEEN_CMD_WHAT_IS_IT
	"Seen Are you hungry?",                                // FLAG_SEEN_CMD_ARE_YOU_HUNGRY
	"Seen What time is it?",                               // FLAG_SEEN_CMD_WHAT_TIME_IS_IT
	"Seen Good dog!",                                      // FLAG_SEEN_CMD_GOOD_DOG
	"Seen Fortune",                                        // FLAG_SEEN_CMD_FORTUNE
	"Seen Boo!",                                           // FLAG_SEEN_CMD_BOO
	"Seen I love you!",                                    // FLAG_SEEN_CMD_I_LOVE_YOU
	"Seen Do a dance!",                                    // FLAG_SEEN_CMD_DO_A_DANCE
	"Seen Sing a song!",                                   // FLAG_SEEN_CMD_SING_A_SONG
	"Seen Shortcake",                                      // FLAG_SEEN_CMD_SHORTCAKE
	"Seen Eclair",                                         // FLAG_SEEN_CMD_ECLAIR
	"Seen Cream Puff",                                     // FLAG_SEEN_CMD_CREAM_PUFF
	"Seen Jelly Roll",                                     // FLAG_SEEN_CMD_JELLY_ROLL
	"Seen Dog Food",                                       // FLAG_SEEN_CMD_DOG_FOOD
	"Seen Ice Cream",                                      // FLAG_SEEN_CMD_ICE_CREAM
	"Seen Rock Paper Scissors",                            // FLAG_SEEN_CMD_ROCK_PAPER_SCISSORS
	
	// 'New!' flag for unlocked colors
	"Seen Sky Blue",                                       // FLAG_SEEN_COLOR_SKY_BLUE
	"Seen Green",                                          // FLAG_SEEN_COLOR_GREEN
	"Seen Red",                                            // FLAG_SEEN_COLOR_RED
	"Seen Pink",                                           // FLAG_SEEN_COLOR_PINK
	"Seen Purple",                                         // FLAG_SEEN_COLOR_PURPLE
	"Seen Gold",                                           // FLAG_SEEN_COLOR_GOLD
	
	// 'New!' flag for unlocked accessories
	"Seen Wappy Badge (blue)",                             // FLAG_SEEN_ACCESSORY_WAPPY_BADGE_1
	"Seen Wappy Badge (pink)",                             // FLAG_SEEN_ACCESSORY_WAPPY_BADGE_2
	"Seen Wappy Badge (yellow)",                           // FLAG_SEEN_ACCESSORY_WAPPY_BADGE_3
	"Seen Star (yellow)",                                  // FLAG_SEEN_ACCESSORY_STAR_1
	"Seen Star (blue)",                                    // FLAG_SEEN_ACCESSORY_STAR_2
	"Seen Star (red)",                                     // FLAG_SEEN_ACCESSORY_STAR_3
	"Seen Heart (pink)",                                   // FLAG_SEEN_ACCESSORY_HEART_1
	"Seen Heart (blue)",                                   // FLAG_SEEN_ACCESSORY_HEART_2
	"Seen Heart (red)",                                    // FLAG_SEEN_ACCESSORY_HEART_3
	"Seen Flower (orange)",                                // FLAG_SEEN_ACCESSORY_FLOWER_1
	"Seen Flower (purple)",                                // FLAG_SEEN_ACCESSORY_FLOWER_2
	"Seen Flower (green)",                                 // FLAG_SEEN_ACCESSORY_FLOWER_3
	"Seen Ribbon (pink)",                                  // FLAG_SEEN_ACCESSORY_RIBBON_1
	"Seen Ribbon (green)",                                 // FLAG_SEEN_ACCESSORY_RIBBON_2
	"Seen Ribbon (yellow)",                                // FLAG_SEEN_ACCESSORY_RIBBON_3
	"Seen Butterfly (purple)",                             // FLAG_SEEN_ACCESSORY_BUTTERFLY_1
	"Seen Butterfly (blue)",                               // FLAG_SEEN_ACCESSORY_BUTTERFLY_2
	"Seen Butterfly (orange)",                             // FLAG_SEEN_ACCESSORY_BUTTERFLY_3
	
	// 'New!' flag for unlocked tricks
	"Seen Shake",                                          // FLAG_SEEN_TRICK_SHAKE
	"Seen Stretch",                                        // FLAG_SEEN_TRICK_STRETCH
	"Seen Grooming",                                       // FLAG_SEEN_TRICK_GROOMING
	"Seen Stand",                                          // FLAG_SEEN_TRICK_STAND
	"Seen Handstand",                                      // FLAG_SEEN_TRICK_HANDSTAND
	"Seen Backflip",                                       // FLAG_SEEN_TRICK_BACKFLIP
	"Seen Happy Dance",                                    // FLAG_SEEN_TRICK_HAPPY_DANCE
	"Seen Show Off",                                       // FLAG_SEEN_TRICK_SHOW_OFF
	"Seen Front Flip",                                     // FLAG_SEEN_TRICK_FRONT_FLIP
	"Seen Double Front Flip",                              // FLAG_SEEN_TRICK_DOUBLE_FRONT_FLIP
	"Seen Triple Front Flip",                              // FLAG_SEEN_TRICK_TRIPLE_FRONT_FLIP
	"Seen Roll Over",                                      // FLAG_SEEN_TRICK_ROLL_OVER
	"Seen Snow Angel",                                     // FLAG_SEEN_TRICK_SNOW_ANGEL
	"Seen Clap",                                           // FLAG_SEEN_TRICK_CLAP
	"Seen Monkey Dance",                                   // FLAG_SEEN_TRICK_MONKEY_DANCE
	"Seen Jump and Flip",                                  // FLAG_SEEN_TRICK_JUMP_AND_FLIP
	"Seen Body Shake",                                     // FLAG_SEEN_TRICK_BODY_SHAKE
	"Seen Hula",                                           // FLAG_SEEN_TRICK_HULA
	"Seen Dizzy",                                          // FLAG_SEEN_TRICK_DIZZY
	"Seen Stand on One Leg",                               // FLAG_SEEN_TRICK_STAND_ON_ONE_LEG
	"Seen Super Handstand!",                               // FLAG_SEEN_TRICK_SUPER_HANDSTAND
	"Seen Breakdance!",                                    // FLAG_SEEN_TRICK_BREAKDANCE
	
	 // Unlocked easy difficulties for travel games
	 "Fruit Catch (Easy)",                                 // FLAG_TRAVEL_GAME_FRUIT_CATCH_EASY
	 "Which one is Wappy? (Easy)",                         // FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_EASY
	 "Wappy's Race (Easy)",                                // FLAG_TRAVEL_GAME_WAPPYS_RACE_EASY
	 "Wappy's Pirate Battle (Easy)",                       // FLAG_TRAVEL_GAME_PIRATE_BATTLE_EASY
	 "Find the Food! (Easy)",                              // FLAG_TRAVEL_GAME_FIND_THE_FOOD_EASY
	
	// Unlocked easy difficulties for home games
	"Fruit Catch (Easy)",                                  // FLAG_HOME_GAME_FRUIT_CATCH_EASY
	"Get the Critters! (Easy)",                            // FLAG_HOME_GAME_GET_THE_CRITTERS_EASY
	"Penguin Run (Easy)",                                  // FLAG_HOME_GAME_PENGUIN_RUN_EASY
	"Target Practice (Easy)",                              // FLAG_HOME_GAME_TARGET_PRACTICE_EASY
	"Where's the Food? (Easy)",                            // FLAG_HOME_GAME_WHERES_THE_FOOD_EASY
	
	// Unlocked normal difficulties for travel games
	"Fruit Catch (Normal)",                                // FLAG_TRAVEL_GAME_FRUIT_CATCH_NORMAL
	"Which one is Wappy? (Normal)",                        // FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_NORMAL
	"Wappy's Race (Normal)",                               // FLAG_TRAVEL_GAME_WAPPYS_RACE_NORMAL
	"Wappy's Pirate Battle (Normal)",                      // FLAG_TRAVEL_GAME_PIRATE_BATTLE_NORMAL
	"Find the Food! (Normal)",                             // FLAG_TRAVEL_GAME_FIND_THE_FOOD_NORMAL
	
	// Unlocked normal difficulties for home games
	"Fruit Catch (Normal)",                                // FLAG_HOME_GAME_FRUIT_CATCH_NORMAL
	"Get the Critters! (Normal)",                          // FLAG_HOME_GAME_GET_THE_CRITTERS_NORMAL
	"Penguin Run (Normal)",                                // FLAG_HOME_GAME_PENGUIN_RUN_NORMAL
	"Target Practice (Normal)",                            // FLAG_HOME_GAME_TARGET_PRACTICE_NORMAL
	"Where's the Food? (Normal)",                          // FLAG_HOME_GAME_WHERES_THE_FOOD_NORMAL
	
	// Unlocked hard difficulties for travel games
	"Fruit Catch (Hard)",                                  // FLAG_TRAVEL_GAME_FRUIT_CATCH_HARD
	"Which one is Wappy? (Hard)",                          // FLAG_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_HARD
	"Wappy's Race (Hard)",                                 // FLAG_TRAVEL_GAME_WAPPYS_RACE_HARD
	"Wappy's Pirate Battle (Hard)",                        // FLAG_TRAVEL_GAME_PIRATE_BATTLE_HARD
	"Find the Food! (Hard)",                               // FLAG_TRAVEL_GAME_FIND_THE_FOOD_HARD
	
	// Unlocked hard difficulties for home games
	"Fruit Catch (Hard)",                                  // FLAG_HOME_GAME_FRUIT_CATCH_HARD
	"Get the Critters! (Hard)",                            // FLAG_HOME_GAME_GET_THE_CRITTERS_HARD
	"Penguin Run (Hard)",                                  // FLAG_HOME_GAME_PENGUIN_RUN_HARD
	"Target Practice (Hard)",                              // FLAG_HOME_GAME_TARGET_PRACTICE_HARD
	"Where's the Food? (Hard)",                            // FLAG_HOME_GAME_WHERES_THE_FOOD_HARD
	
	// "New!" flag for unlocked easy difficulties for travel games
	"Seen Fruit Catch (Easy)",                             // FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_EASY
	"Seen Which one is Wappy? (Easy)",                     // FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_EASY
	"Seen Wappy's Race (Easy)",                            // FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_EASY
	"Seen Wappy's Pirate Battle (Easy)",                   // FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_EASY
	"Seen Find the Food! (Easy)",                          // FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_EASY
	
	// "New!" flag for unlocked easy difficulties for home games
	"Seen Fruit Catch (Easy)",                             // FLAG_SEEN_HOME_GAME_FRUIT_CATCH_EASY
	"Seen Get the Critters! (Easy)",                       // FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_EASY
	"Seen Penguin Run (Easy)",                             // FLAG_SEEN_HOME_GAME_PENGUIN_RUN_EASY
	"Seen Target Practice (Easy)",                         // FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_EASY
	"Seen Where's the Food? (Easy)",                       // FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_EASY
	
	// "New!" flag for unlocked normal difficulties for travel games
	"Seen Fruit Catch (Normal)",                           // FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_NORMAL,
	"Seen Which one is Wappy? (Normal)",                   // FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_NORMAL,
	"Seen Wappy's Race (Normal)",                          // FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_NORMAL,
	"Seen Wappy's Pirate Battle (Normal)",                 // FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_NORMAL,
	"Seen Find the Food! (Normal)",                        // FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_NORMAL,
	
	// "New!" flag for unlocked normal difficulties for home games
	"Seen Fruit Catch (Normal)",                           // FLAG_SEEN_HOME_GAME_FRUIT_CATCH_NORMAL,
	"Seen Get the Critters! (Normal)",                     // FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_NORMAL,
	"Seen Penguin Run (Normal)",                           // FLAG_SEEN_HOME_GAME_PENGUIN_RUN_NORMAL,
	"Seen Target Practice (Normal)",                       // FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_NORMAL,
	"Seen Where's the Food? (Normal)",                     // FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_NORMAL,
	
	// "New!" flag for unlocked hard difficulties for travel games
	"Seen Fruit Catch (Hard)",                             // FLAG_SEEN_TRAVEL_GAME_FRUIT_CATCH_HARD,
	"Seen Which one is Wappy? (Hard)",                     // FLAG_SEEN_TRAVEL_GAME_WHICH_ONE_IS_WAPPY_HARD,
	"Seen Wappy's Race (Hard)",                            // FLAG_SEEN_TRAVEL_GAME_WAPPYS_RACE_HARD,
	"Seen Wappy's Pirate Battle (Hard)",                   // FLAG_SEEN_TRAVEL_GAME_PIRATE_BATTLE_HARD,
	"Seen Find the Food! (Hard)",                          // FLAG_SEEN_TRAVEL_GAME_FIND_THE_FOOD_HARD,
	
	// "New!" flag for unlocked hard difficulties for home games
	"Seen Fruit Catch (Hard)",                             // FLAG_SEEN_HOME_GAME_FRUIT_CATCH_HARD,
	"Seen Get the Critters! (Hard)",                       // FLAG_SEEN_HOME_GAME_GET_THE_CRITTERS_HARD,
	"Seen Penguin Run (Hard)",                             // FLAG_SEEN_HOME_GAME_PENGUIN_RUN_HARD,
	"Seen Target Practice (Hard)",                         // FLAG_SEEN_HOME_GAME_TARGET_PRACTICE_HARD,
	"Seen Where's the Food? (Hard)",                       // FLAG_SEEN_HOME_GAME_WHERES_THE_FOOD_HARD,
	
	// Flag if viewed message boxes
	"Seen food message box",                               // FLAG_SEEN_MESSAGE_FOOD
	"Seen toys message box",                               // FLAG_SEEN_MESSAGE_TOYS
	"Seen cleaning message box",                           // FLAG_SEEN_MESSAGE_CLEANING
	"Seen intro message boxes",                            // FLAG_SEEN_MESSAGE_INTRO
	
	// Unused flags (set to 0 in new save file)
	"Unused (302)",                                        // FLAG_UNUSED_302
	"Unused (303)",                                        // FLAG_UNUSED_303
	"Unused (304)",                                        // FLAG_UNUSED_304
	"Unused (305)",                                        // FLAG_UNUSED_305
	"Unused (306)",                                        // FLAG_UNUSED_306
	"Unused (307)",                                        // FLAG_UNUSED_307
	"Unused (308)",                                        // FLAG_UNUSED_308
	"Unused (309)",                                        // FLAG_UNUSED_309
	"Unused (310)",                                        // FLAG_UNUSED_310
	"Unused (311)",                                        // FLAG_UNUSED_311
	"Unused (312)",                                        // FLAG_UNUSED_312
	"Unused (313)",                                        // FLAG_UNUSED_313
	"Unused (314)",                                        // FLAG_UNUSED_314
	"Unused (315)",                                        // FLAG_UNUSED_315
	"Unused (316)",                                        // FLAG_UNUSED_316
	"Unused (317)",                                        // FLAG_UNUSED_317
	"Unused (318)",                                        // FLAG_UNUSED_318
	"Unused (319)"                                         // FLAG_UNUSED_319
};


typedef enum {
	COLOR_START = 0,
	COLOR_BLUE,                                            // 0
	COLOR_GREEN,                                           // 1
	COLOR_RED,                                             // 2
	COLOR_PINK,                                            // 3
	COLOR_PURPLE,                                          // 4
	COLOR_GOLD,                                            // 5
	COLOR_MAX
} WDColor;

static const char* WDColorStr[] = {
	"Sky Blue",                                            // COLOR_BLUE
	"Green",                                               // COLOR_GREEN
	"Red",                                                 // COLOR_RED
	"Pink",                                                // COLOR_PINK
	"Purple",                                              // COLOR_PURPLE
	"Gold"                                                 // COLOR_GOLD
};


typedef enum {
	ACCESSORY_START = 0,
	
	ACCESSORY_NONE = 0,                                    // 0
	
	ACCESSORY_WAPPY_BADGE_1,                               // 1
	ACCESSORY_WAPPY_BADGE_2,                               // 2
	ACCESSORY_WAPPY_BADGE_3,                               // 3
	
	ACCESSORY_STAR_1,                                      // 4
	ACCESSORY_STAR_2,                                      // 5
	ACCESSORY_STAR_3,                                      // 6
	
	ACCESSORY_HEART_1,                                     // 7
	ACCESSORY_HEART_2,                                     // 8
	ACCESSORY_HEART_3,                                     // 9
	
	ACCESSORY_FLOWER_1,                                    // 10
	ACCESSORY_FLOWER_2,                                    // 11
	ACCESSORY_FLOWER_3,                                    // 12
	
	ACCESSORY_RIBBON_1,                                    // 13
	ACCESSORY_RIBBON_2,                                    // 14
	ACCESSORY_RIBBON_3,                                    // 15
	
	ACCESSORY_BUTTERFLY_1,                                 // 16
	ACCESSORY_BUTTERFLY_2,                                 // 17
	ACCESSORY_BUTTERFLY_3,                                 // 18
	
	ACCESSORY_MAX
} WDAccessory;

static const char* WDAccessoryStr[] = {
	"(None)",                                              // ACCESSORY_NONE
	
	"Wappy Badge (blue)",                                  // ACCESSORY_WAPPY_BADGE_1
	"Wappy Badge (pink)",                                  // ACCESSORY_WAPPY_BADGE_2
	"Wappy Badge (yellow)",                                // ACCESSORY_WAPPY_BADGE_3
	
	"Star (yellow)",                                       // ACCESSORY_STAR_1
	"Star (blue)",                                         // ACCESSORY_STAR_2
	"Star (red)",                                          // ACCESSORY_STAR_3
	
	"Heart (pink)",                                        // ACCESSORY_HEART_1
	"Heart (blue)",                                        // ACCESSORY_HEART_2
	"Heart (red)",                                         // ACCESSORY_HEART_3
	
	"Flower (orange)",                                     // ACCESSORY_FLOWER_1
	"Flower (purple)",                                     // ACCESSORY_FLOWER_2
	"Flower (green)",                                      // ACCESSORY_FLOWER_3
	
	"Ribbon (pink)",                                       // ACCESSORY_RIBBON_1
	"Ribbon (green)",                                      // ACCESSORY_RIBBON_2
	"Ribbon (yellow)",                                     // ACCESSORY_RIBBON_3
	
	"Butterfly (purple)",                                  // ACCESSORY_BUTTERFLY_1
	"Butterfly (blue)",                                    // ACCESSORY_BUTTERFLY_2
	"Butterfly (orange)"                                   // ACCESSORY_BUTTERFLY_3
};


typedef enum {
	ROOM_START = 0,
	ROOM_LIVING_ROOM = 0,                                  // 0
	ROOM_GARDEN,                                           // 1
	ROOM_BEDROOM,                                          // 2
	ROOM_KITCHEN,                                          // 3
	ROOM_ROOFTOP,                                          // 4
	ROOM_MAX
} WDRoom;

static const char* WDRoomStr[] = {
	"Living Room",                                         // ROOM_LIVING_ROOM
	"Garden",                                              // ROOM_GARDEN
	"Bedroom",                                             // ROOM_BEDROOM
	"Kitchen",                                             // ROOM_KITCHEN
	"Rooftop"                                              // ROOM_ROOFTOP
};


typedef enum {
	PERSONALITY_START = 0,
	PERSONALITY_NAUGHTY = 0,                               // 0
	PERSONALITY_CHEERFUL,                                  // 1
	PERSONALITY_BIG_EATER,                                 // 2
	PERSONALITY_NEAT_FREAK,                                // 3
	PERSONALITY_MAX
} WDPersonality;

static const char* WDPersonalityStr[] = {
	"Naughty",                                             // PERSONALITY_NAUGHTY
	"Cheerful",                                            // PERSONALITY_CHEERFUL
	"Big Eater",                                           // PERSONALITY_BIG_EATER
	"Neat Freak"                                           // PERSONALITY_NEAT_FREAK
};


typedef enum {
	MINIGAME_START = 0,
	
	MINIGAME_HOME_START = 0,
	MINIGAME_HOME_FRUIT_CATCH = 0,                         // 0
	MINIGAME_HOME_GET_THE_CRITTERS,                        // 1
	MINIGAME_HOME_PENGUIN_RUN,                             // 2
	MINIGAME_HOME_TARGET_PRACTICE,                         // 3
	MINIGAME_HOME_WHERES_THE_FOOD,                         // 4
	MINIGAME_HOME_MAX,
	
	MINIGAME_TRAVEL_START = 5,
	MINIGAME_TRAVEL_FRUIT_CATCH = 5,                       // 5
	MINIGAME_TRAVEL_WHICH_ONE_IS_WAPPY,                    // 6
	MINIGAME_TRAVEL_WAPPYS_RACE,                           // 7
	MINIGAME_TRAVEL_PIRATE_BATTLE,                         // 8
	MINIGAME_TRAVEL_FIND_THE_FOOD,                         // 9
	MINIGAME_TRAVEL_MAX,
	
	MINIGAME_MAX = MINIGAME_TRAVEL_MAX
} WDMinigame;

static const char* WDMinigameStr[] = {
	"Fruit Catch",                                         // MINIGAME_HOME_FRUIT_CATCH
	"Get the Critters!",                                   // MINIGAME_HOME_GET_THE_CRITTERS
	"Penguin Run",                                         // MINIGAME_HOME_PENGUIN_RUN
	"Target Practice",                                     // MINIGAME_HOME_TARGET_PRACTICE
	"Where's the Food?",                                   // MINIGAME_HOME_WHERES_THE_FOOD
	
	"Fruit Catch",                                         // MINIGAME_TRAVEL_FRUIT_CATCH
	"Which one is Wappy?",                                 // MINIGAME_TRAVEL_WHICH_ONE_IS_WAPPY
	"Wappy's Race",                                        // MINIGAME_TRAVEL_WAPPYS_RACE
	"Wappy's Pirate Battle",                               // MINIGAME_TRAVEL_PIRATE_BATTLE
	"Find the Food!"                                       // MINIGAME_TRAVEL_FIND_THE_FOOD
};


typedef enum {
	DIFFICULTY_START = 0,
	DIFFICULTY_EASY = 0,                                   // 0
	DIFFICULTY_NORMAL,                                     // 1
	DIFFICULTY_HARD,                                       // 2
	DIFFICULTY_MAX
} WDMinigameDifficulty;

static const char* WDMinigameDifficultyStr[] = {
	"Easy",                                                // DIFFICULTY_EASY
	"Normal",                                              // DIFFICULTY_NORMAL
	"Hard"                                                 // DIFFICULTY_HARD
};


typedef enum {
	TRICK_START = 0,
	TRICK_SHAKE = 0,                                       // 0
	TRICK_STRETCH,                                         // 1
	TRICK_GROOMING,                                        // 2
	TRICK_STAND,                                           // 3
	TRICK_HANDSTAND,                                       // 4
	TRICK_BACKFLIP,                                        // 5
	TRICK_HAPPY_DANCE,                                     // 6
	TRICK_SHOW_OFF,                                        // 7
	TRICK_FRONT_FLIP,                                      // 8
	TRICK_DOUBLE_FRONT_FLIP,                               // 9
	TRICK_TRIPLE_FRONT_FLIP,                               // 10
	TRICK_ROLL_OVER,                                       // 11
	TRICK_SNOW_ANGEL,                                      // 12
	TRICK_CLAP,                                            // 13
	TRICK_MONKEY_DANCE,                                    // 14
	TRICK_JUMP_AND_FLIP,                                   // 15
	TRICK_BODY_SHAKE,                                      // 16
	TRICK_HULA,                                            // 17
	TRICK_DIZZY,                                           // 18
	TRICK_STAND_ON_ONE_LEG,                                // 19
	TRICK_SUPER_HANDSTAND,                                 // 20
	TRICK_BREAKDANCE,                                      // 21
	TRICK_MAX
} WDTrick;

static const char* WDTrickStr[] = {
	"Shake",                                               // TRICK_SHAKE
	"Stretch",                                             // TRICK_STRETCH
	"Grooming",                                            // TRICK_GROOMING
	"Stand",                                               // TRICK_STAND
	"Handstand",                                           // TRICK_HANDSTAND
	"Backflip",                                            // TRICK_BACKFLIP
	"Happy Dance",                                         // TRICK_HAPPY_DANCE
	"Show Off",                                            // TRICK_SHOW_OFF
	"Front Flip",                                          // TRICK_FRONT_FLIP
	"Double Front Flip",                                   // TRICK_DOUBLE_FRONT_FLIP
	"Triple Front Flip",                                   // TRICK_TRIPLE_FRONT_FLIP
	"Roll Over",                                           // TRICK_ROLL_OVER
	"Snow Angel",                                          // TRICK_SNOW_ANGEL
	"Clap",                                                // TRICK_CLAP
	"Monkey Dance",                                        // TRICK_MONKEY_DANCE
	"Jump and Flip",                                       // TRICK_JUMP_AND_FLIP
	"Body Shake",                                          // TRICK_BODY_SHAKE
	"Hula",                                                // TRICK_HULA
	"Dizzy",                                               // TRICK_DIZZY
	"Stand on One Leg",                                    // TRICK_STAND_ON_ONE_LEG
	"Super Handstand!",                                    // TRICK_SUPER_HANDSTAND
	"Breakdance!"                                          // TRICK_BREAKDANCE
};

#ifdef __cplusplus
}
#endif

#endif
