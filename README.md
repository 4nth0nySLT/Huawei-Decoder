# Huawei-Decoder Python Module
Decode $2...$

### Online version
https://anthiago.com/h2o/get

### Install
```
python setup.py install
```

### Problems with install?
```
c++ -O3 -Wall -shared -std=c++11 -fPIC -Iinclude $(python -m pybind11 --includes) decoder.cpp -o decoder$(python-config --extension-suffix)
```

### Usage
```
from decoder import decoder

key=decoder("$2*Zan:&lt;plZJ[bbBFkv0U3=$VR0D$d4R&quot;#H1A3*k&apos;6$")

print(key) # "lascuatromarias"
```

### Example error 
```
from decoder import decoder

key=decoder("$2 ... /r ...$") # Incorrect
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
UnicodeDecodeError: 'utf-8' codec can't decode byte 0xb8 in position 1: invalid start byte

key=decoder("$2 ... //r ...$") # Correct
```

### Detect invalid string

```
>>> decoder("$2*Zan:&lt;plZJ[bbBFkv0U3=$VR0D$d4R&quot;#H1A3*k&ap$")
'Invalid'
>>> decoder("$2*Zan:&lt;plZJ[bbBFkv0U3=$VR0D$d4R&quot;#H1A3*k&apos;6$")
'lascuatromarias'
```
