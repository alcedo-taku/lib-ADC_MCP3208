# Mcp3208_reader

## mcp3208tについて

[mcp3208t](https://akizukidenshi.com/catalog/g/gI-00238/)とは12bitのADC用のicでこのクラスはこのicとspi通信を行いadcされた値を取得するクラスです

## CubeMx
```yaml
PinOut : SPIn
            SPIn_NSSに設定されているピンをGPIO_outputに変更
SPIn
    - Mode = Full-Duplex Master
      Hardware Signal = Disable
    
    Parameter setting
        Basic parameter
            - Frame Format = Motorola
            - Data Size = 8bit
            - First bit = MSBfirst
        
        Clock parameter
            - Prescaler = (APB1 Timer Periferal 1 [MHz]/ 1)その下のbaud rateが1000.0KBit/sになるように設定
            - Clock Polality = Low
            - clock Phase = 1 edge
```
## 列挙

### ADC_CHANNEL
```c++
	enum class ADC_CHANNEL:uint8_t{
		CH_0,
		CH_1,
		CH_2,
		CH_3,
		CH_4,
		CH_5,
		CH_6,
		CH_7
	};
```
mcp3208tのチャンネルの指定に使います

## コンストラクタ

#### Mcp3208t_reader::Mcp3208t_reader(SPI_HandleTypeDef& hspi,GPIO_TypeDef *nss_port, uint16_t nss_pin)
使うSPIのハンドル,NSS_pinの代わりに設定したGPIOのポートを指定する。
```c++
//例
Mcp3208t_reader mcp3208t_reader(hspi1,GPIOA,GPIO_PIN_4);
```

## 関数

#### void Mcp3208t_reader::init()
mcp3208tと通信する準備をします
```c++
//例
mcp3208t_reader.init();
```

#### void Mcp3208t_reader::update(ADC_CHANNEL adc_channel, uint32_t timeout)
指定したチャンネルのadcのカウントを更新します
```c++
//例
mcp3208t_reader.update(ADC_CHANNEL::CH_0, 0xF);
```

#### uint16_t Mcp3208t_reader::get(ADC_CHANNEL adc_channel)
指定したチャンネルのadcのカウントを取得します
```c++
//例
range_sensor_value[0] = mcp3208t_reader.get(ADC_CHANNEL::CH_0);
```

