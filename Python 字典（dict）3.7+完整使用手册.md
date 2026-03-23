# Python 字典（dict）3.7+完整使用手册

# Python 字典（dict）完整使用手册

## 文档说明

本文档全面覆盖 Python 字典**基础操作、高级用法、实用场景、异常处理、性能优化、类型注解**，补充原资料缺失内容，形成可直接用于学习/开发的完整字典手册，适配 Python 3.7+ 版本（字典默认有序）。

---

## 目录

1. 字典核心概念

2. 基础增删改查（补充完整）

3. 安全访问与默认值（扩展）

4. 遍历、解构与解包（补充）

5. 字典合并、复制与推导式（补充）

6. 键/值操作高级方法

7. 嵌套字典安全操作（优化）

8. 实用场景：分组/统计/缓存/配置

9. 有序字典与特殊字典

10. 字典作为数据结构替代方案

11. 异常处理与避坑指南

12. 性能优化最佳实践

13. 类型注解（Python 3.9+）

14. 高频面试考点

---

## 1. 字典核心概念

- 字典是**可变、无序（Python3.7+有序）、键唯一**的键值对（key-value）数据结构

- **键（key）**：必须是不可变类型（字符串、数字、元组），不可重复

- **值（value）**：任意类型（列表、字典、对象等），可重复

- 核心特性：**O(1) 时间复杂度查找**，是 Python 最高效的数据结构之一

---

## 2. 基础增删改查（完整版）

### 2.1 创建字典（补充空字典、元组键、推导式创建）

```Python

# 1. 空字典
d = {}
d = dict()

# 2. 基础创建
d = {'name': 'Alice', 'age': 30}
d = dict(name='Alice', age=30)
d = dict([('name', 'Alice'), ('age', 30)])  # 可迭代对象创建

# 3. 元组作为键（不可变类型）
d = {(1, 2): '坐标', 'id': 1001}

# 4. 固定键+默认值快速创建
keys = ['a', 'b', 'c']
d = dict.fromkeys(keys, 0)  # {'a':0, 'b':0, 'c':0}
```

### 2.2 访问值（补充异常捕获）

```Python

d = {'name': 'Alice', 'age': 30}

# 直接访问（键不存在抛 KeyError）
print(d['name'])

# 安全访问（推荐）
print(d.get('age'))        # 存在返回值，不存在返回 None
print(d.get('gender', '未知'))  # 自定义默认值

# 强制访问+捕获异常
try:
    print(d['gender'])
except KeyError:
    print("键不存在")
```

### 2.3 新增/修改（补充批量操作）

```Python

# 单键修改/新增
d['age'] = 31
d['city'] = '北京'

# 批量更新（键存在覆盖，不存在新增）
d.update({'age': 32, 'gender': '女'})

# 元组解包更新
d.update([('height', 165), ('weight', 55)])
```

### 2.4 删除操作（补充返回值、条件删除）

```Python

d = {'name': 'Alice', 'age': 30, 'city': '北京'}

# 1. del 语句（无返回值，键不存在报错）
del d['city']

# 2. pop() 删除并返回值（键不存在可指定默认值）
age = d.pop('age')
d.pop('gender', '键不存在')  # 不报错

# 3. popitem() 删除最后插入的键值对（Python3.7+）
d.popitem()

# 4. 清空字典
d.clear()

# 5. 条件删除（删除值为指定内容的键）
d = {'a':1, 'b':2, 'c':1}
d = {k:v for k, v in d.items() if v != 1}
```

---

## 3. 安全访问与默认值（扩展）

### 3.1 setdefault 进阶用法

```Python

d = {}
# 键不存在 → 设置默认值并返回；键存在 → 直接返回值
d.setdefault('user', {}).setdefault('name', 'Bob')
# 结果：{'user': {'name': 'Bob'}}
```

### 3.2 defaultdict 全类型支持

```Python

from collections import defaultdict

# 常用默认类型
dd_int = defaultdict(int)      # 默认 0
dd_list = defaultdict(list)    # 默认空列表
dd_dict = defaultdict(dict)    # 默认空字典
dd_str = defaultdict(str)      # 默认空字符串

# 自定义默认工厂函数
def default():
    return "未定义"
dd_custom = defaultdict(default)
```

---

## 4. 遍历、解构与解包（补充）

### 4.1 遍历（补充反向遍历、带索引遍历）

```Python

d = {'a':1, 'b':2, 'c':3}

# 反向遍历（Python3.7+）
for k in reversed(d):
    print(k, d[k])

# 带索引遍历
for idx, (k, v) in enumerate(d.items()):
    print(idx, k, v)
```

### 4.2 解包（补充函数传参、多层解包）

```Python

# 字典解包为关键字参数（**）
def info(name, age):
    print(name, age)

person = {'name': 'Alice', 'age': 30}
info(**person)

# 合并解包（函数多参数）
def full_info(**kwargs):
    print(kwargs)
full_info(**person, city='北京')
```

---

## 5. 字典合并、复制与推导式（补充）

### 5.1 合并（补充多字典合并）

```Python

d1, d2, d3 = {'a':1}, {'b':2}, {'c':3}

# Python3.5+ 多字典合并
merged = {**d1, **d2, **d3}

# Python3.9+ 运算符
merged = d1 | d2 | d3
```

### 5.2 复制（浅拷贝/深拷贝，关键补充）

```Python

import copy

# 浅拷贝（只拷贝第一层，嵌套字典共享内存）
d = {'user': {'name': 'Alice'}}
d1 = d.copy()
d2 = dict(d)
d3 = {**d}

# 深拷贝（完全独立，推荐嵌套字典使用）
d4 = copy.deepcopy(d)
d['user']['name'] = 'Bob'
print(d1['user']['name'])  # Bob（浅拷贝受影响）
print(d4['user']['name'])  # Alice（深拷贝独立）
```

### 5.3 字典推导式（补充复杂逻辑）

```Python

# 键值互换（值必须唯一）
d = {'a':1, 'b':2}
reverse_d = {v: k for k, v in d.items()}

# 多条件过滤+计算
d = {'apple': 5, 'banana': 2, 'orange': 8}
new_d = {k: v*2 for k, v in d.items() if v > 3}
```

---

## 6. 键/值操作高级方法

```Python

d = {'name': 'Alice', 'age': 30}

# 获取所有键/值/键值对（视图对象，动态更新）
keys = d.keys()    # dict_keys(['name', 'age'])
values = d.values()
items = d.items()

# 转换为列表
key_list = list(keys)

# 判断键是否存在
print('name' in d)
print('gender' not in d)

# 获取字典长度
print(len(d))
```

---

## 7. 嵌套字典安全操作（优化版）

### 7.1 安全获取深层值

```Python

config = {
    'db': {
        'host': '127.0.0.1',
        'user': {'name': 'admin'}
    }
}

# 方法1：链式 get（推荐）
host = config.get('db', {}).get('host', '默认地址')
pwd = config.get('db', {}).get('user', {}).get('pwd', '123456')

# 方法2：通用深度获取函数
def deep_get(dic, path, default=None):
    keys = path.split('.')
    for key in keys:
        dic = dic.get(key, {})
        if not dic:
            return default
    return dic

# 使用
print(deep_get(config, 'db.user.name'))  # admin
print(deep_get(config, 'db.user.pwd'))   # None
```

### 7.2 嵌套字典赋值

```Python

# 安全赋值（不存在则创建）
from collections import defaultdict

def nested_dict():
    return defaultdict(nested_dict)

d = nested_dict()
d['user']['info']['age'] = 30
```

---

## 8. 实用场景（补充完整）

### 8.1 分组聚合

```Python

from collections import defaultdict, Counter

# 按条件分组
data = [('男', '张三'), ('女', '李四'), ('男', '王五')]
groups = defaultdict(list)
for gender, name in data:
    groups[gender].append(name)

# 频率统计
nums = [1,2,1,3,2,1]
cnt = Counter(nums)
print(cnt.most_common(2))  # 出现次数最多的2个元素
```

### 8.2 缓存/记忆化

```Python

# 手动缓存
cache = {}
def func(x):
    if x in cache:
        return cache[x]
    res = x * 2
    cache[x] = res
    return res

# 装饰器缓存
from functools import lru_cache
@lru_cache(maxsize=None)
def fib(n):
    return n if n < 2 else fib(n-1)+fib(n-2)
```

### 8.3 配置文件管理

```Python

# 读取/更新配置
config = {
    'debug': True,
    'port': 8080
}
if config['debug']:
    print("开发模式")
```

---

## 9. 有序字典与特殊字典

### 9.1 OrderedDict（显式有序操作）

```Python

from collections import OrderedDict
od = OrderedDict([('a',1), ('b',2)])
od.move_to_end('a')        # 移到末尾
od.move_to_end('b', last=False)  # 移到开头
```

### 9.2 ChainMap（合并多个字典，不创建新对象）

```Python

from collections import ChainMap
d1 = {'a':1}
d2 = {'b':2}
cm = ChainMap(d1, d2)
print(cm['a'])  # 高效查找，无需合并
```

---

## 10. 字典作为数据结构替代方案

### 10.1 替代简易类

```Python

# 字典存储数据
user = {'name': 'Alice', 'age': 30}

# SimpleNamespace（支持.属性访问）
from types import SimpleNamespace
user_obj = SimpleNamespace(**user)
print(user_obj.name)
```

### 10.2 替代 switch 语句（Python 无switch）

```Python

def add(a, b): return a+b
def sub(a, b): return a-b

op = {
    '+': add,
    '-': sub
}
print(op['+'](1,2))  # 3
```

---

## 11. 异常处理与避坑指南

### 11.1 常见异常

```Python

d = {}
# KeyError：访问不存在的键
# TypeError：键为可变类型（如列表）
d = {[1,2]: 'a'}  # 报错！列表不能做键
```

### 11.2 避坑点

1. **字典键必须不可变**：列表、字典不能做键

2. **浅拷贝风险**：嵌套字典必须用 `deepcopy`

3. **遍历同时删除**：会报错，需先转列表

    ```Python
    
    d = {'a':1, 'b':2}
    for k in list(d):  # 转列表安全遍历
        if k == 'a':
            del d[k]
    ```

---

## 12. 性能优化最佳实践

1. **优先用字典查找**：替代多重 if-else，速度提升 10 倍以上

2. **大数据量预分配**：`dict.fromkeys` 预创建

3. **避免频繁创建字典**：复用对象

4. **`get()`** ** 优于 ** **`try/except`**：简单场景更高效

5. **`collections`** ** 工具**：比手动实现快且简洁

---

## 13. 类型注解（Python 3.9+）

```Python

# 基础注解
from typing import Dict, Optional

# 键：str，值：int
d: Dict[str, int] = {'age': 30}

# 可选值
user: Dict[str, Optional[str]] = {'name': 'Alice', 'gender': None}
```

---

## 14. 高频面试考点

1. Python3.7+ 字典**默认有序**

2. 字典查找时间复杂度：**O(1)**

3. 浅拷贝 vs 深拷贝区别

4. `defaultdict`/`Counter`/`OrderedDict` 适用场景

5. 字典键必须是**不可变类型**

---

### 文档总结

1. 本手册覆盖**字典从基础到高级**全场景用法，可直接用于开发/学习/面试

2. 核心亮点：补充**深拷贝、嵌套安全操作、类型注解、异常处理、性能优化**

3. 所有代码适配 Python 3.7+，直接复制即可运行

4. 结构化清晰，可按场景快速检索对应用法
> （注：文档部分内容可能由 AI 生成）