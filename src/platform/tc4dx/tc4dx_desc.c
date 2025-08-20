/**
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (c) Bao Project and Contributors. All rights reserved.
 */

#include <platform.h>

#ifdef GENERATING_DEFS
uint32_t plat_ints[] = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69,
    70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93,
    94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 106, 107, 120, 121, 122, 126, 127, 128, 132, 133,
    135, 136, 140, 141, 142, 143, 144, 145, 146, 147, 148, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 172, 173, 174, 175, 176, 177, 178, 179, 180,
    181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218,
    219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237,
    238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 260,
    261, 262, 263, 264, 265, 266, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292,
    293, 294, 295, 296, 297, 298, 299, 300, 301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311,
    312, 313, 314, 315, 316, 317, 318, 319, 336, 337, 340, 341, 342, 343, 344, 345, 346, 347, 348,
    349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367,
    368, 369, 370, 371, 372, 373, 376, 377, 378, 380, 381, 382, 384, 385, 386, 388, 389, 390, 391,
    392, 393, 394, 395, 396, 397, 398, 399, 400, 401, 402, 403, 404, 405, 406, 407, 408, 409, 410,
    411, 412, 436, 440, 441, 442, 443, 444, 445, 446, 447, 448, 449, 450, 451, 452, 453, 454, 455,
    456, 460, 461, 462, 463, 464, 465, 466, 467, 468, 469, 470, 471, 472, 473, 474, 475, 476, 477,
    478, 479, 480, 481, 482, 483, 484, 485, 486, 487, 488, 489, 490, 491, 492, 493, 494, 495, 496,
    497, 498, 499, 500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514, 515,
    516, 517, 518, 519, 520, 521, 522, 523, 524, 525, 526, 527, 528, 529, 530, 531, 532, 533, 534,
    535, 536, 537, 538, 539, 540, 541, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 553,
    554, 555, 556, 557, 558, 559, 560, 561, 562, 563, 564, 565, 566, 567, 568, 569, 570, 571, 572,
    573, 574, 575, 576, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 587, 588, 589, 590, 591,
    592, 593, 594, 595, 604, 608, 609, 610, 611, 612, 613, 614, 615, 616, 617, 618, 619, 620, 621,
    622, 623, 624, 625, 626, 627, 628, 629, 630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640,
    641, 642, 643, 644, 645, 646, 647, 648, 649, 650, 651, 652, 653, 654, 655, 656, 657, 658, 659,
    660, 661, 662, 663, 664, 665, 666, 667, 668, 669, 670, 671, 736, 737, 740, 741, 742, 743, 744,
    745, 746, 747, 748, 749, 750, 751, 752, 753, 754, 755, 756, 757, 758, 759, 760, 764, 765, 766,
    767, 768, 769, 770, 771, 772, 773, 774, 775, 776, 777, 778, 779, 780, 781, 782, 783, 784, 788,
    789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 801, 802, 803, 804, 805, 806, 807,
    808, 809, 810, 811, 812, 813, 814, 815, 816, 817, 818, 819, 820, 821, 822, 823, 824, 825, 826,
    827, 828, 829, 830, 831, 832, 833, 834, 835, 836, 837, 838, 839, 840, 841, 842, 843, 844, 845,
    846, 847, 848, 849, 850, 851, 852, 853, 854, 855, 856, 857, 858, 859, 860, 861, 862, 863, 864,
    865, 866, 867, 884, 885, 886, 887, 888, 889, 890, 891, 892, 893, 894, 895, 900, 901, 902, 903,
    904, 905, 906, 907, 908, 909, 910, 911, 912, 913, 914, 915, 916, 917, 918, 919, 920, 921, 922,
    923, 948, 949, 950, 951, 952, 953, 954, 955, 956, 957, 958, 959, 1076, 1077, 1078, 1079, 1080,
    1081, 1132, 1133, 1134, 1135, 1136, 1137, 1138, 1139, 1140, 1141, 1144, 1145, 1146, 1147, 1148,
    1149, 1150, 1151, 1152, 1153, 1156, 1157, 1160, 1161, 1162, 1163, 1164, 1165, 1166, 1167, 1168,
    1169, 1170, 1171, 1172, 1173, 1174, 1175, 1176, 1177, 1178, 1179, 1180, 1181, 1182, 1183, 1184,
    1185, 1188, 1190, 1192, 1193, 1194, 1195, 1196, 1197, 1198, 1199, 1204, 1205, 1206, 1207, 1208,
    1209, 1210, 1211, 1212, 1213, 1216, 1217, 1218, 1219, 1220, 1221, 1222, 1224, 1225, 1226, 1227,
    1228, 1229, 1230, 1231, 1232, 1233, 1234, 1235, 1236, 1237, 1238, 1239, 1248, 1249, 1250, 1251,
    1252, 1253, 1254, 1255, 1256, 1257, 1258, 1259, 1260, 1261, 1262, 1263, 1264, 1265, 1266, 1267,
    1268, 1269, 1270, 1271, 1272, 1273, 1276, 1277, 1278, 1279, 1280, 1281, 1282, 1283, 1284, 1285,
    1286, 1287, 1288, 1289, 1290, 1291, 1292, 1293, 1294, 1295, 1296, 1297, 1300, 1301, 1304, 1305,
    1306, 1307, 1308, 1309, 1310, 1311, 1312, 1313, 1314, 1315, 1316, 1317, 1318, 1319, 1320, 1321,
    1322, 1323, 1324, 1325, 1326, 1327, 1328, 1329, 1330, 1331, 1332, 1333, 1334, 1335, 1336, 1337,
    1338, 1339, 1340, 1341, 1342, 1343, 1344, 1345, 1346, 1347, 1348, 1349, 1350, 1351, 1352, 1353,
    1354, 1355, 1356, 1357, 1358, 1359, 1360, 1361, 1362, 1363, 1364, 1365, 1366, 1367, 1368, 1369,
    1370, 1371, 1372, 1373, 1374, 1375, 1376, 1377, 1378, 1379, 1380, 1381, 1382, 1383, 1924, 1927,
    1928, 1929, 1930, 1940, 1944, 1945, 1946, 1947, 1948, 1949, 1950, 1951, 1952, 1953, 1954, 1955,
    1956, 1957, 1958, 1959, 1960, 1961, 1962, 1963, 1964, 1965, 1966, 1967, 1992, 1993, 1994, 1995,
    1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009, 2010, 2011,
    2012, 2013, 2014, 2015, 2024, 2025, 2026, 2027, 2028, 2029, 2030, 2031, 2032, 2033, 2034,
    2035 };
const uint32_t plat_int_size = sizeof(plat_ints) / 4;
#endif

const struct plat_device dev_array[] = {
    {
        // WTU
        .dev_base = 0xF0000000,
        .prot_num = 8,
        .prot_addr = (unsigned long[]){ 0x18, 0x48, 0x78, 0xA8, 0xD8, 0x108, 0x150, 0x184 },
        .apu_num = 8,
        .apu_addr = (unsigned long[]){ 0x1C, 0x4C, 0x7C, 0xAC, 0xDC, 0x10C, 0x154, 0x188 },
    },
    {
        // SCU
        .dev_base = 0xF0024000,
        .prot_num = 4,
        .prot_addr = (unsigned long[]){ 0x18, 0x1C, 0x20, 0x24 },
        .apu_num = 6,
        .apu_addr = (unsigned long[]){ 0x28, 0x48, 0x68, 0x88, 0xA8, 0xC8 },
    },
    {
        // SMU
        .dev_base = 0xF0028000,
        .prot_num = 6,
        .prot_addr = (unsigned long[]){ 0x78, 0x7C, 0x3FC, 0x400, 0x13FC, 0x1400 },
        .apu_num = 4,
        .apu_addr = (unsigned long[]){ 0x80, 0x404, 0x1404, 0x1904 },
    },
    {
        // P00
        .dev_base = 0xF003A000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P01
        .dev_base = 0xF003A400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P02
        .dev_base = 0xF003A800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P03
        .dev_base = 0xF003AC00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P04
        .dev_base = 0xF003B000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P10
        .dev_base = 0xF003C800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P13
        .dev_base = 0xF003D400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P14
        .dev_base = 0xF003D800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P15
        .dev_base = 0xF003DC00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P16
        .dev_base = 0xF003E000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P20
        .dev_base = 0xF003F000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P21
        .dev_base = 0xF003F400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P22
        .dev_base = 0xF003F800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P23
        .dev_base = 0xF003FC00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P25
        .dev_base = 0xF0040400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P30
        .dev_base = 0xF0041800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P31
        .dev_base = 0xF0041C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P32
        .dev_base = 0xF0042000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P33
        .dev_base = 0xF0042400,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },//0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P34
        .dev_base = 0xF0042800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P35
        .dev_base = 0xF0042C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // P40
        .dev_base = 0xF0044000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x30 },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x90, 0xB0, 0xD0, 0xF0, 0x110, 0x130, 0x150 },
    },
    {
        // SMM
        .dev_base = 0xF0060000,
        .prot_num = 10,
        .prot_addr = (unsigned long[]){ 0xC, 0x10, 0x14, 0x58, 0x5C, 0x60, 0x64, 0x68, 0x6C, 0x70 },
        .apu_num = 2,
        .apu_addr = (unsigned long[]){ 0x18, 0x38 },
    },
    {
        // CCU
        .dev_base = 0xF0064000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TRI
        .dev_base = 0xF0068000,
        .prot_num = 3,
        .prot_addr = (unsigned long[]){ 0x20, 0x24, 0x28 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // VTMON
        .dev_base = 0xF006C000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // SCR.XRAM
        .dev_base = 0xF0240000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // SCR.PER.SFR
        .dev_base = 0xF0248000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // PMS
        .dev_base = 0xF0249000,
        .prot_num = 3,
        .prot_addr = (unsigned long[]){ 0x9000, 0x9004, 0x9028 },
        .apu_num = 2,
        .apu_addr = (unsigned long[]){ 0x900C, 0x902C },
    },
    {
        // DMTU0 (VMT?)
        .dev_base = 0xF0400000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU1
        .dev_base = 0xF0420000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU2
        .dev_base = 0xF0440000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU3
        .dev_base = 0xF0460000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU4
        .dev_base = 0xF0480000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU5
        .dev_base = 0xF04A0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU6
        .dev_base = 0xF04C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DMTU7
        .dev_base = 0xF04E0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // SBCU
        .dev_base = 0xF1FFFC00,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0xC, 0x10 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x14 },
    },
    {
        // HSPHY
        .dev_base = 0xF2000000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 4,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0 },
    },
    {
        // MSC0
        .dev_base = 0xF4400800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x18 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // QSPI0
        .dev_base = 0xF4401000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI1
        .dev_base = 0xF4401200,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI2
        .dev_base = 0xF4401400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI3
        .dev_base = 0xF4401600,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI4
        .dev_base = 0xF4401800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI5
        .dev_base = 0xF4401A00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI6
        .dev_base = 0xF4401C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // QSPI7
        .dev_base = 0xF4401E00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // FCE0
        .dev_base = 0xF4402E00,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 3,
        .apu_addr = (unsigned long[]){ 0x44, 0x64, 0x84 },
    },
    {
        // SENT0
        .dev_base = 0xF4403000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x18, 0x1C },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // SENT1
        .dev_base = 0xF4404000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x18, 0x1C },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // PSI5
        .dev_base = 0xF4405000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // PSI5S0
        .dev_base = 0xF4407000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // DMA0
        .dev_base = 0xF4410000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x24, 0x28 },
        .apu_num = 16,
        .apu_addr = (unsigned long[]){ 0x1000, 0x1080, 0x1100, 0x1180, 0x1200, 0x1280, 0x1300,
            0x1380, 0x1400, 0x1480, 0x1500, 0x1580, 0x1600, 0x1680, 0x1700, 0x1780 },
    },
    {
        // DMA1
        .dev_base = 0xF4414000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x24, 0x28 },
        .apu_num = 16,
        .apu_addr = (unsigned long[]){ 0x1000, 0x1080, 0x1100, 0x1180, 0x1200, 0x1280, 0x1300,
            0x1380, 0x1400, 0x1480, 0x1500, 0x1580, 0x1600, 0x1680, 0x1700, 0x1780 },
    },
    {
        // ERAY0
        .dev_base = 0xF441C000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x900, 0x904 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x900 },
    },
    {
        // ERAY1
        .dev_base = 0xF441D000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x900, 0x904 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x900 },
    },
    {
        // IR.SFR (REMOVE)
        .dev_base = 0xF4430000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // IR.SRC (REMOVE)
        .dev_base = 0xF4432000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // HSSL0
        .dev_base = 0xF4480000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // HSCT0
        .dev_base = 0xF4490000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // HSSL1
        .dev_base = 0xF44A0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // HSCT1
        .dev_base = 0xF44B0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // I2C0
        .dev_base = 0xF44C0000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10020 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x10040 },
    },
    {
        // I2C1
        .dev_base = 0xF44E0000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10020 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x10040 },
    },
    {
        // I2C2
        .dev_base = 0xF4500000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10020 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x10040 },
    },
    {
        // PCIe1.SFR
        .dev_base = 0xF46A0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0, 0xC0 },
    },
    {
        // PCIe0.SFR
        .dev_base = 0xF46A8000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0, 0xC0 },
    },
    {
        // SDMMC0
        .dev_base = 0xF46B0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x20, 0x24 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN0
        .dev_base = 0xF46C0000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN1
        .dev_base = 0xF46C0200,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN2
        .dev_base = 0xF46C0400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN3
        .dev_base = 0xF46C0600,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN4
        .dev_base = 0xF46C0800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN5
        .dev_base = 0xF46C0A00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN6
        .dev_base = 0xF46C0C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN7
        .dev_base = 0xF46C0E00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN8
        .dev_base = 0xF46C1000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN9
        .dev_base = 0xF46C1200,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN10
        .dev_base = 0xF46C1400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN11
        .dev_base = 0xF46C1600,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN12
        .dev_base = 0xF46C1800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN13
        .dev_base = 0xF46C1A00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN14
        .dev_base = 0xF46C1C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN15
        .dev_base = 0xF46C1E00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN16
        .dev_base = 0xF46C2000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN17
        .dev_base = 0xF46C2200,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN18
        .dev_base = 0xF46C2400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN19
        .dev_base = 0xF46C2600,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN20
        .dev_base = 0xF46C2800,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN21
        .dev_base = 0xF46C2A00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN22
        .dev_base = 0xF46C2C00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN23
        .dev_base = 0xF46C2E00,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN24
        .dev_base = 0xF46C3000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN25
        .dev_base = 0xF46C3200,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN26
        .dev_base = 0xF46C3400,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // ASCLIN27
        .dev_base = 0xF46C3600,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x40 },
    },
    {
        // CAN0.SRAM
        .dev_base = 0xF4700000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CAN0.SFR
        .dev_base = 0xF4710000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x30, 0x100, 0x500, 0x900, 0xD00 },
    },
    {
        // CAN1.SRAM
        .dev_base = 0xF4720000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CAN1.SFR
        .dev_base = 0xF4730000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10018 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x10030, 0x10100, 0x10500, 0x10900, 0x10D00 },
    },
    {
        // CAN2.SRAM
        .dev_base = 0xF4740000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CAN2.SFR
        .dev_base = 0xF4750000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10018 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x10030, 0x10100, 0x10500, 0x10900, 0x10D00 },
    },
    {
        // CAN3.SRAM
        .dev_base = 0xF4760000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CAN3.SFR
        .dev_base = 0xF4770000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10018 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x10030, 0x10100, 0x10500, 0x10900, 0x10D00 },
    },
    {
        // CAN4.SRAM
        .dev_base = 0xF4780000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CAN4.SFR
        .dev_base = 0xF4790000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x10018 },
        .apu_num = 5,
        .apu_addr = (unsigned long[]){ 0x10030, 0x10100, 0x10500, 0x10900, 0x10D00 },
    },
    {
        // CANXL0.SRAM
        .dev_base = 0xF47C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CANXL0.SFR
        .dev_base = 0xF47D0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x10038, 0x1003C },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0x10018, 0x10100, 0x10200, 0x10300, 0x10400 },
    },
    {
        // ADC.SFR
        .dev_base = 0xF5000000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TMADC.SFR
        .dev_base = 0xF501F800,
        .prot_num = 17,
        .prot_addr = (unsigned long[]){ 0xC, 0x80, 0x84, 0x88, 0x8C, 0x90, 0x94, 0x98, 0x8C, 0xA0,
            0xA4, 0xA8, 0xAC, 0xB0, 0xB4, 0xB8, 0xBC },
        .apu_num = 16,
        .apu_addr = (unsigned long[]){ 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180, 0x1A0, 0x1C0,
            0x1E0, 0x200, 0x220, 0x240, 0x260, 0x280, 0x2A0 },
    },
    {
        // TMADC0
        .dev_base = 0xF5020000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TMADC1
        .dev_base = 0xF5020800,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TMADC2
        .dev_base = 0xF5021000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TMADC3
        .dev_base = 0xF5021800,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CDSP.SFR
        .dev_base = 0xF50BF800,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CDSP0
        .dev_base = 0xF50C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CDSP1
        .dev_base = 0xF50C2000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CBCU
        .dev_base = 0xF5FFFC00,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CSCU
        .dev_base = 0xF6000000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TRNG
        .dev_base = 0xF6000200,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // PKC
        .dev_base = 0xF6010000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CSBCU
        .dev_base = 0xF6FFFC00,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0xC, 0x10 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x14 },
    },
    {
        // NVM.FSI_HOST
        .dev_base = 0xF8008000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NV.FSI_CSRM
        .dev_base = 0xF8028000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.DMU(incl. SFR)
        .dev_base = 0xF8040000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.DMU(host cmd seq)
        .dev_base = 0xF8080000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.DMU(cs cmd seq)
        .dev_base = 0xF80C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU0.FSFR
        .dev_base = 0xF8400000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB00.UR
        .dev_base = 0xF8410000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB01.UR
        .dev_base = 0xF8418000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU1.FSFR
        .dev_base = 0xF8440000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB10.UR
        .dev_base = 0xF8450000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB11.UR
        .dev_base = 0xF8458000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU2.FSFR
        .dev_base = 0xF8480000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB20.UR
        .dev_base = 0xF8490000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB21.UR
        .dev_base = 0xF8498000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU3.FSFR
        .dev_base = 0xF84C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB30.UR
        .dev_base = 0xF84D0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB31.UR
        .dev_base = 0xF84D8000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU4.FSFR
        .dev_base = 0xF8500000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB40.UR
        .dev_base = 0xF8510000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB41.UR
        .dev_base = 0xF8518000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU5.FSFR
        .dev_base = 0xF8540000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB50.UR
        .dev_base = 0xF8550000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWB51.UR
        .dev_base = 0xF8558000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPUcs.FSFR
        .dev_base = 0xF8580000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // NVM.PFRWBcs.UR
        .dev_base = 0xF8590000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU0.SFR
        .dev_base = 0xF8800000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU0.HR1.CSFR
        .dev_base = 0xF8810000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU0.HR2.CSFR
        .dev_base = 0xF8820000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU0.HR0.CSFR
        .dev_base = 0xF8830000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU1.SFR
        .dev_base = 0xF8840000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU1.HR1.CSFR
        .dev_base = 0xF8850000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU1.HR2.CSFR
        .dev_base = 0xF8860000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU1.HR0.CSFR
        .dev_base = 0xF8870000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU2.SFR
        .dev_base = 0xF8880000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU2.HR1.CSFR
        .dev_base = 0xF8890000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU2.HR2.CSFR
        .dev_base = 0xF88A0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU2.HR0.CSFR
        .dev_base = 0xF88B0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU3.SFR
        .dev_base = 0xF88C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU3.HR1.CSFR
        .dev_base = 0xF88D0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU3.HR2.CSFR
        .dev_base = 0xF88E0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU3.HR0.CSFR
        .dev_base = 0xF88F0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU4.SFR
        .dev_base = 0xF8900000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU4.HR1.CSFR
        .dev_base = 0xF8910000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU4.HR2.CSFR
        .dev_base = 0xF8920000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU4.HR0.CSFR
        .dev_base = 0xF8930000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU5.SFR
        .dev_base = 0xF8940000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU5.HR1.CSFR
        .dev_base = 0xF8950000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU5.HR2.CSFR
        .dev_base = 0xF8960000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPU5.HR0.CSFR
        .dev_base = 0xF8970000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPUcs.SFR
        .dev_base = 0xF8980000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CPUcs.HR1.CSFR
        .dev_base = 0xF8990000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CSS
        .dev_base = 0xF8D00000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // SRI0.SFR
        .dev_base = 0xF8F00000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI1.SFR
        .dev_base = 0xF8F10000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI2.SFR
        .dev_base = 0xF8F20000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI3.SFR
        .dev_base = 0xF8F30000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI4.SFR
        .dev_base = 0xF8F40000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI5.SFR
        .dev_base = 0xF8F50000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI6.SFR
        .dev_base = 0xF8F60000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // SRI7.SFR
        .dev_base = 0xF8F70000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x4E0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x4C0 },
    },
    {
        // GETH0.SFR
        .dev_base = 0xF9000000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x24 },
        .apu_num = 11,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140,
            0x160, 0x180 },
    },
    {
        // GETH0.RAM
        .dev_base = 0xF9020000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // DRE.SFR
        .dev_base = 0xF9030000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x18, 0x1C },
        .apu_num = 7,
        .apu_addr = (unsigned long[]){ 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0 },
    },
    {
        // DRE.RAM
        .dev_base = 0xF9038000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // xSPI.SFR
        .dev_base = 0xF9040000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x20 },
        .apu_num = 9,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE, 0x100, 0x120, 0x140 },
    },
    {
        // eGTM.CLUSTER0
        .dev_base = 0xF9080000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // eGTM.CLUSTER1
        .dev_base = 0xF90A0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // eGTM.CLUSTER2
        .dev_base = 0xF90C0000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // eGTM.SFR
        .dev_base = 0xF90E0000,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0x1C, 0x1D0 },
        .apu_num = 7,
        .apu_addr =
            (unsigned long[]){
                0x24,
                0x48,
                0x6C,
                0x1D4,
                0x1F8,
                0x21C,
                0x240,
            },
    },
    {
        // LETH0
        .dev_base = 0xF9400000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x24 },
        .apu_num = 13,
        .apu_addr = (unsigned long[]){ 0x40, 0x60, 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140,
            0x160, 0x180, 0x1A0, 0x1C0 },
    },
    {
        // PPU.STUDMI
        .dev_base = 0xF9810000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // PPU.DEBUG
        .dev_base = 0xF9820000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // PPU.SAFETY
        .dev_base = 0xF9830000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // PPU.AP
        .dev_base = 0xF9840000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x0 },
        .apu_num = 3,
        .apu_addr = (unsigned long[]){ 0x20, 0x40, 0x60 },
    },
    {
        // PPU.CSM.AP
        .dev_base = 0xF9850000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // PPU.VMEM.AP
        .dev_base = 0xF9860000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x0 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // LLI.SFR
        .dev_base = 0xF9900000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x1C },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x20 },
    },
    {
        // MCDS4P (incl. TBUF32k)
        .dev_base = 0xFA000000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // MCDS2P (incl. TBUF16k)
        .dev_base = 0xFA040000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TRIF
        .dev_base = 0xFA100000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // CBS
        .dev_base = 0xFA180000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
    {
        // TBCU
        .dev_base = 0xFAFFFC00,
        .prot_num = 2,
        .prot_addr = (unsigned long[]){ 0xC, 0x10 },
        .apu_num = 1,
        .apu_addr = (unsigned long[]){ 0x14 },
    },
    {
        // LMU0.SFR (REMOVE? Part of memory management)
        .dev_base = 0xFB000000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU1.SFR
        .dev_base = 0xFB010000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU2.SFR
        .dev_base = 0xFB020000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU3.SFR
        .dev_base = 0xFB030000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU4.SFR
        .dev_base = 0xFB040000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU5.SFR
        .dev_base = 0xFB050000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU6.SFR
        .dev_base = 0xFB060000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU7.SFR
        .dev_base = 0xFB070000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU8.SFR
        .dev_base = 0xFB080000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // LMU9.SFR
        .dev_base = 0xFB090000,
        .prot_num = 1,
        .prot_addr = (unsigned long[]){ 0x28 },
        .apu_num = 17,
        .apu_addr = (unsigned long[]){ 0x80, 0xA0, 0xC0, 0xE0, 0x100, 0x120, 0x140, 0x160, 0x180,
            0x1A0, 0x1C0, 0x1E0, 0x200, 0x220, 0x240, 0x260, 0x300 },
    },
    {
        // PCIe0.DATA
        .dev_base = 0xFC000000,
        .prot_num = 0,
        .prot_addr = (unsigned long[]){ 0 },
        .apu_num = 0,
        .apu_addr = (unsigned long[]){ 0 },
    },
};

struct platform platform = {

    .cpu_num = 6,
    .cpu_master_fixed = true,
    .cpu_master = 0,

    .region_num = 8,
    .regions =  (struct mem_region[]) {

#ifdef MEM_NON_UNIFIED
        {
            .base = 0xA0000000,
            .size = 0x400000,
            .perms = MEM_RX,
        },
#endif
        {
            // DLMU0
            .base = 0x90000000,
            .size = 0x100000,
            .perms = MEM_RWX,
        },
#ifndef MEM_NON_UNIFIED
        {
            // DLMU1
            .base = 0x90080000,
            .size =   0x80000,
            .perms = MEM_RWX,
        },
#endif  
        {
            // CPU0.DSPR, 240Kb
            .base = 0x70000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },  
        {
            // CPU1.DSPR, 240Kb
            .base = 0x60000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },  
        {
            // CPU2.DSPR, 240Kb
            .base = 0x50000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },  
        {
            // CPU3.DSPR, 240Kb
            .base = 0x40000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
        {
            // CPU4.DSPR, 240Kb
            .base = 0x30000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },  
        {
            // CPU5.DSPR, 240Kb
            .base = 0x20000000,
            .size =   0x3C000,
            .perms = MEM_RWX,
        },
    },
    .mmio_region_num = 1,
    .mmio_regions = (struct mem_region[]) {
        {
            .base = 0xF0000000,
            .size = 0xFFF0000,
        },
    },
    .arch = {
        .ir = {
            .int_addr = 0xF4430000,
            .src_addr = 0xF4432000,
            .GPSR_offset = 0x700,
            .GPSR_size = (0xB00 + (8*4)) - 0x700,
        },
        .device_num = sizeof(dev_array)/sizeof(struct plat_device),
        .devices = dev_array,
    },

    .console = {
        .base = 0xF46C0000, //ASCLIN0
    },
};
