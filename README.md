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

