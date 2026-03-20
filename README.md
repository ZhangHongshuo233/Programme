# programme

这是一个 C 语言与数据结构练习仓库，包含课程练习、算法题与一个小型搜索性能测试项目。

## 目录说明

- `c programme/`: 基础 C 练习与小题目
- `fds data structures and algorithums/`: 数据结构与排序实现
- `fds probelms/`: 算法题练习（含部分 C/Python 版本）
- `project1/code/`: 搜索算法性能测试代码与结果
- `scripts/`: Git 自动同步脚本

## 本地开发

1. 在 VS Code 中直接修改代码。
2. 需要本地编译时，可按文件单独编译运行（示例）：

```bash
gcc "fds data structures and algorithums/seqque.c" -o seqque
./seqque
```

Windows PowerShell 下执行示例：

```powershell
gcc "fds data structures and algorithums/seqque.c" -o seqque.exe
.\seqque.exe
```

## Git 托管方式

当前仓库已连接 GitHub 远程仓库，并启用了自动提交模式：

- 计划任务名：`ProgrammeGitAutoSync`
- 执行频率：每 5 分钟
- 执行逻辑：`git add -A` -> `git commit` -> `git push origin main`

自动提交信息格式：

```text
chore(auto-sync): snapshot YYYY-MM-DD HH:mm:ss
```

## 常用命令

手动立刻同步一次：

```powershell
schtasks /Run /TN "ProgrammeGitAutoSync"
```

查看任务状态：

```powershell
schtasks /Query /TN "ProgrammeGitAutoSync" /V /FO LIST
```

暂停自动同步：

```powershell
schtasks /Change /TN "ProgrammeGitAutoSync" /Disable
```

恢复自动同步：

```powershell
schtasks /Change /TN "ProgrammeGitAutoSync" /Enable
```

## 说明

- 本仓库以学习记录为主，目录命名保持原始练习习惯。
- 建议后续逐步补充每个子目录的题目说明与输入输出示例，方便复习和展示。

## 题目清单

### c programme（C 练习题，约 72 个 .c 文件）

- 1024.c
- acrostic_chinese.c
- acrostic_decoder.c
- attribute_cards.c
- Binary_search.c
- calculat_pi.c
- calc_words_len.c
- cleared_str_of_hex_to_decimal.c
- clipStringByTwoChars.c
- command_line_args.c
- decimal _to_binary.c
- dicimal_to_hexcimal.c
- exam.5-1.c
- exchange_coins.c
- find_book.c
- find_local_max_in_matrix.c
- find_the_biggest_char.c
- Find_The_Integer.c
- how.c
- id_checker.c
- IP.transformation.c
- matrix_multiply.c
- matrix_row_sum.c
- max_cnt.c
- min_str.c
- month_day.c
- non_commen_elements.c
- practice.c
- qucik_sort_str.c
- Reversed_Array.c
- right_rotate_array.c
- rotate_array.c
- Rotate_Matrix.c
- search.c
- sequence_difference.c
- simple_calculator.c
- Simplified_Insertion_Sort.c
- spiral_matrix.c
- string_zip.c
- str_capitalize.c
- student_manage.c
- Symmetric_Difference_Of_Arrays.c
- test1.c
- test2.c
- test3.c
- test4.c
- test7.c
- time_conversion.c
- upper_triangular_matrix_check.c
- variable_array.c
- YangHui_Triangle.c
- 中缀表达式求值.c
- 二分查找.c
- 二级指针操作实例.c
- 分段函数.c
- 对齐.c
- 找完数.c
- 指定位置输出字符串.c
- 换钱.c
- 梅森素数.c
- 水仙花数.c
- 求100以内所有偶数的和.c
- 求一批整数中出现最多的个位数字.c
- 求三角形面积.c
- 求幂级数展开的部分和.c
- 求平均成绩.c
- 相邻字母间用-链接.c
- 相邻字母间用空格链接(1).c
- 计算火车运行时间.c
- 输出三角形字符阵列.c
- 逆序的三位数.c
- 逐位分割数字.c

### fds data structures and algorithums（数据结构实现）

- Bubble_Sort.c
- doulink.c
- Insertion_Sort.c
- linked_list.c
- linkstack.c
- Quick_Sort.c
- Selection_Sort.c
- seqque.c
- Stack_test.c
- test1.c

头文件：

- doulink.h
- linkstack.h
- node.h
- seqque.h
- tree.h

### fds probelms（算法题）

- 3sum.c
- add_two_polynimials.c
- BalloonPopping.c
- maxSubArray.c
- merge_lists.c
- TrappingRainWater.c
- WaterContainer.c

Python 对照实现：

- maxSubArray.py
- TrappingRainWater.py
- watercontainer.py

## 学习进度表

可按下面格式手动维护：

| 模块 | 总数 | 已完成 | 进行中 | 待开始 | 备注 |
|---|---:|---:|---:|---:|---|
| c programme 基础题 | 72 | 0 | 0 | 72 | 可按题型分组（字符串/数组/数学） |
| FDS 数据结构实现 | 10 | 0 | 0 | 10 | 建议先队列、栈、链表，再排序 |
| FDS 算法题（C） | 7 | 0 | 0 | 7 | 结合 LeetCode 思路复盘 |
| Python 对照实现 | 3 | 0 | 0 | 3 | 对比同题 C/Python 写法 |

每周建议更新一次，并在已完成题目后补上：题意、关键思路、复杂度。
