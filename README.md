# Mcp3208t_reader

ADCIC MCP3208とspi通信を行い、ADCされた値を取得するライブラリ

## MCP3208について
12bitのADCIC。SPI通信により値を取得することができる。  
[MCP3208](https://akizukidenshi.com/catalog/g/gI-00238/)

## CubeMx
```yaml
Pinout
- SPIn
- SSピンとして任意のピンを GPIO_output に変更
SPIn
- Mode
    - Mode              = Full-Duplex Master
    - Hardware Signal   = Disable

- Parameter setting
    - Basic parameter
        - Frame Format  = Motorola
        - Data Size     = 8bit
        - First bit     = MSBfirst
    
    - Clock parameter
        - Prescaler         = (APB1 Timer Periferal 1 [MHz]/ 1)その下のbaud rateが1000.0KBit/sになるように設定
        - Clock Polality    = Low
        - clock Phase       = 1Edge
```

## サンプルプログラム

### コンストラクタ
```c++
Mcp3208t_reader mcp3208t_reader(hspi1,GPIOA,GPIO_PIN_4);
```

### 初期化
```c++
mcp3208t_reader.init();
```

### 更新と取得
```c++
mcp3208t_reader.update(ADC_CHANNEL::CH_0, 0xF);
range_sensor_value[0] = mcp3208t_reader.get(ADC_CHANNEL::CH_0);
```
