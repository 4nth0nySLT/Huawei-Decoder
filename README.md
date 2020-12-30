# Huawei-Decoder Python Module
Decode $2...$

### Install
```
python setup.py install
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

# from UnicodeDecodeError return Invalid
key=decoder("$2 ... /r ...$") # Incorrect

print(key) # "Invalid"

key=decoder("$2 ... //r ...$") # Correct

```
