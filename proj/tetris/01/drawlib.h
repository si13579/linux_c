#ifndef DRAWLIB_H__
#define DRAWLIB_H__

#include <inttypes.h>
#include <stdio.h>

#define BLOCK_TYPE_NULL 0
#define BLOCK_TYPE_WALL 1
#define BLOCK_TYPE_NORMAL_MIN 2

typedef enum
{
    ACTION_EMPTY,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_DOWN,
    ACTION_FAST_DOWN,
    ACTION_ROTATE,
    ACTION_PAUSE,
    ACTION_SAVE,
    ACTION_LOAD,
    ACTION_NEW_GAME,
    ACTION_UNRECOGNIZED
} Action;

// 坐标位置必须是有符号数
typedef int16_t Coordinate;
typedef uint8_t BlockType;

// 初始化控制台
void prepare_console(void);

// 恢复控制台到进入游戏前状态
void restore_console(void);

// 清屏
void clear_screen(void);

// 绘制一个方块
void print_block(BlockType type);

// 清除颜色，输出文字前调用
void clear_color(void);

// 设置输出光标的位置
void set_cursor_absolute_position(Coordinate x, Coordinate y);

// 获取玩家动作，有wait_time毫秒的时间等待输入
Action get_action(uint32_t wait_time);

#endif
