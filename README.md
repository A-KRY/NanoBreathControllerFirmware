# NanoBreathControllerFirmware

[English Version](#README_en-US)

[中文版](#README_zh-CN)

[日本語版](#README_ja-JP)

# README_en-US

## 1. Introduction
This project is for MIDI breath controller firmware, based on the Arduino Nano development board. You will also need to create or purchase a pressure sensor module (preferably with an appropriately amplified circuit). The upper computer driver can be found at [NanoBreathControllerUSBDriver](https://github.com/A-KRY/NanoBreathControllerUSBDriver), and it is independent of the specific model of the pressure sensor.

The author used the XGZP040 pressure sensor. You only need to read data from your pressure sensor module, standardize it to MIDI CC values in the range of $[0,127]$, and send it to the upper computer via the serial port.

## 2. Installation

1. This project is written using JetBrains CLion. It is recommended to deploy JetBrains CLion.
2. Open JetBrains CLion, go to **File → Settings → Plugins**, search for and install PlatformIO for CLion.
3. Go to **File → New → Project from Version Control**, select and import the URL of this repository.
4. For ease of debugging, it is recommended to install Arduino IDE.

## 3. Running
### 3.1 Hardware Connection
This project uses the XGZP040 pressure sensor, and it is a pre-packaged PCB module, requiring only the connection of VCC, GND, and AOUT pins. The author's connection is as follows:

| Arduino Nano | XGZP040 |
| ------------ | ------- |
| 5V           | VCC     |
| GND          | GND     |
| A7           | AOUT    |

Please connect the power and data lines according to the actual situation of your pressure sensor.

### 3.2 Software Modification

The core of the code is the **setup()**, **loop()**, and **sendDataTask()** functions, which are not complex.

**setup()** sets the serial port baud rate, **loop()** calls **sendDataTask()** and delays. **sendDataTask()** reads the pressure sensor value standardized to the range of MIDI CC values and sends it via the serial port.

The **getNext()** method reads the data and returns the MIDI CC value, while **mapper()** functions as the force curve.

The main modification is for the pressure sensor module.

#### 3.2.1 Pressure Sensor as Analog Output

If your pressure module is **analog output**, modify **ANALOG_IN** in **main.h** to the pin you connected. Modify **sendDataTask()** as follows and burn it. Open Arduino IDE, connect the device, open the serial monitor, and set the baud rate to $115200$ (or another value consistent with **setup()**), blow air and observe the range of Arduino Nano ADC output values.

```C++
void sendDataTask() {
    if (Serial) {
		DEBUG(analogRead(ANALOG_IN))
    }
}
```

Adjust **ADC_MIN** and **ADC_MAX** in **main.h** based on the range of values your module outputs. **mapper()** takes care of the force curve. If you need a different force curve shape, you can modify the expression inside **mapper()**, but be sure to read the comments for that method.

If you want to change the sampling rate, change the value in the **delay()** in **loop()**. The highest sampling rate of the ADC on the Arduino Nano is 10 kHz, so the minimum would be:

```C++
delayMicroseconds(100);
```

#### 3.2.2 Pressure Sensor as Digital Output

This section only outlines the idea.

For most ADC chips, there will be a pin level change indicating that the conversion is complete and the sampled value can be read. You can configure an interrupt for the corresponding pin to trigger subsequent tasks. The interrupt service routine should be brief. You can use a task flag + polling approach. The overall structure is as follows. Of course, you can also try using embedded operating systems like FreeRTOS, not only it is not known whether the Arduino Nano can handle it, but also to this simple task there're no needs.

```C++
// Task flag
bool sendDataTaskFlag = false;

// Your interrupt service routine
void onInterruptTriggered() {
    // Should be as short as possible, so only set the task flag
    sendDataTaskFlag = true;
}

void setup() {
    // Set up the interrupt
    attachInterrupt(YOUR_PIN, onInterruptTriggered);
    // Complete other configurations
}

void loop() {
    if (sendDataTaskFlag) {
        // Reset the task flag
        sendDataTaskFlag = false;
        // Execute the task
        sendDataTask();
    }
}
```

Based on the usage manual of your ADC chip, write the driver for reading data (if using formats like SPI, I2C, etc., you can directly use Arduino's built-in functions). [Blow air and observe the range of ADC](#321-pressure-sensor-as-analog-output), and replace the **analogRead(ANALOG_IN)** in the line that assigns **normalized** in **main.cpp**'s **getNext()** with your method of reading the ADC input.

### 3.3 Uploading to Arduino Nano

In JetBrains CLion, locate the PlatformIO icon (typically found at the top right in the new UI). Double-click **Upload** to flash the firmware to your Arduino Nano.

### 3.4 Contact

If you have any questions or feedback, you can contact me via [email](mailto:aliothkry@proton.me).

## 4. Dependencies and Open Source Project Declaration

This project makes use of the following open-source projects and tools:

- [PlatformIO](https://platformio.org/): A cross-platform development tool for embedded systems development.
- [Arduino](https://www.arduino.cc/): An open-source hardware and software ecosystem for building embedded applications.

Please note that these open-source projects have their own licensing agreements. For more details, please refer to the respective project's licensing documents.

## 5. License Agreement

This project is governed by the GNU GPL-v3. For detailed information, please refer to the [LICENSE](LICENSE) file.

We extend our gratitude to the open-source communities of PlatformIO and Arduino for providing us with these excellent tools and resources.

<center><i>Translation generated by ChatGPT.</i></center>



# README_zh-CN

## 1. 简介
本项目用于 MIDI 呼吸控制器固件。顾名思义，基于 Arduino Nano 开发板。您还需要制作或购买气压传感器模块（最好包含增益适当的放大电路）。上位机驱动见 [NanoBreathControllerUSBDriver](https://github.com/A-KRY/NanoBreathControllerUSBDriver)，且与气压传感器的具体型号无关。

作者使用的气压传感器为 XGZP040。您只需从您的气压传感器模块读取数据，标准化为 $[0,127]$ 的 MIDI CC 值并通过串口发送至上位机即可。

## 2. 安装

1. 本项目使用 JetBrains CLion 编写。建议您部署 JetBrains CLion。
2. 打开 JetBrains CLion，选择 **文件—设置—插件** ，搜索并安装 PlatformIO for CLion 。
3. **文件—新建—来自版本控制的项目**，选择并导入本仓库 URL。
5. 为方便调试，推荐安装 Arduino IDE

## 3. 运行
### 3.1 硬件连接
本项目使用 XGZP040 气压传感器，且是封装好的 PCB 模块，只需连接 VCC、GND、AOUT 引脚。作者的连接方式为

| Arduino Nano | XGZP040 |
| ------------ | ------- |
| 5V           | VCC     |
| GND          | GND     |
| A7           | AOUT    |

请根据您的气压传感器的实际情况连好电源线和数据线。

### 3.2 软件修改

代码的核心是**setup()**、**loop()**、**sendDataTask()** 三个函数，并不复杂。

**setup()** 设置串口波特率，**loop()** 调用 **sendDataTask()** 并延时。**sendDataTask()** 读取标准化至 MIDI CC 取值范围的气压传感器数值并通过串口发送。

**getNext() **方法读取数据并返回 MIDI CC 值，**mapper()** 方法承担力度曲线的作用。

主要的修改针对气压传感器模块。

#### 3.2.1 气压传感器为模拟输出

如果您的气压模块是**模拟输出**，将 **main.h** 中的 **ANALOG_IN** 修改为您连接的引脚。修改 **sendDataTask()** 如下并烧录，打开 Arduino IDE 、连接设备并打开串口监视器，将波特率设为 $115200$（或与 **setup()** 中一致的其他值），吹气观察 Arduino Nano ADC 输出值的范围。

```C++
void sendDataTask() {
    if (Serial) {
		DEBUG(analogRead(ANALOG_IN))
    }
}
```

根据您输出数值的范围，调整 **main.h** 中 **ADC_MIN** 和 **ADC_MAX** 。**mapper()** 承担力度曲线的功能。如果您需要其他的力度曲线形状，可修改 **mapper()** 内的表达式，但务必注意阅读该方法的注释。

**若想修改采样率**，更改 **loop()** 中的 **delay()** 的数值即可。Arduino Nano 片上 ADC 的最高采样率是10kHz，即最小为

```C++
delayMicroseconds(100);
```

#### 3.2.2 气压传感器为数字输出

这一部分仅说明思路。

对于大多数 ADC 芯片而言，会有一个引脚的电平发生变化表示转化完成可以读取采样值。您可以为相应引脚配置中断来触发后续任务。中断服务程序应简短，您可以采用任务标志+轮询的方式，整体结构如下。当然您也可以尝试使用 FreeRTOS 等嵌入式操作系统，但首先不知道 Arduino Nano 能否负担起，其次这种简单任务也没必要。

```C++
// 任务标志
bool sendDataTaskFlag = false;

// 您的中断服务程序
void onInterruptTriggered() {
    // 应尽量简短，因此只设置任务标志
    sendDataTaskFlag = true;
}

void setup() {
    // 设置中断
    attachInterrupt(YOUR_PIN, onInterruptTriggered);
    // 完成其他配置
}

void loop() {
    if (sendDataTaskFlag) {
        // 重置任务标志
        sendDataTaskFlag = false;
        // 执行任务
        sendDataTask();
    }
}
```

根据您的 ADC 芯片的使用手册编写读取数据的驱动（如果采用 SPI、I2C 等格式，直接使用 Arduino 内置函数即可），[吹气观察 ADC 的范围](#321-气压传感器为模拟输出)，将 **main.cpp** 中 **getNext()** 的 **normalized** 的赋值一行中的 **analogRead(ANALOG_IN)** 替换为您的读取 ADC 输入的方法。

### 3.3 烧录至 Arduino Nano

JetBrains CLion中，找到 PlatformIO 图标（在新版 UI 下是右侧顶部），双击 **Upload** 即可烧录。

### 3.4 联系作者

如果您有任何疑问或反馈，可发送[邮件](mailto:aliothkry@proton.me)。

## 4. 依赖和开源项目声明

本项目使用了以下开源项目和工具：

- [PlatformIO](https://platformio.org/): 一个跨平台的开发工具，用于嵌入式系统开发。
- [Arduino](https://www.arduino.cc/): 一个开源硬件和软件生态系统，用于构建嵌入式应用程序。

请注意，这些开源项目有它们自己的许可协议。有关详细信息，请参阅各个项目的许可协议文件。

## 5. 许可协议

本项目使用 GNU GPL-v3 许可协议。有关详细信息，请参阅 [LICENSE](LICENSE) 文件。

感谢PlatformIO和Arduino等开源社区，提供了出色的工具和资源。



# README_ja-JP


## 1. 概要

このプロジェクトは、MIDIブレスコントローラのファームウェア用です。名前からもわかる通り、Arduino Nanoボードをベースにしています。圧力センサーモジュール（適切な増幅回路を含むことが望ましい）を作成または購入する必要があります。上位コンピュータードライバーは、[NanoBreathControllerUSBDriver](https://github.com/A-KRY/NanoBreathControllerUSBDriver)で提供されており、圧力センサーの具体的なモデルには関係ありません。

著者が使用した圧力センサーはXGZP040です。圧力センサーモジュールからデータを読み取り、MIDI CC値（0から127の範囲に標準化）をシリアルポート経由で上位コンピュータに送信するだけです。

## 2. インストール

1. このプロジェクトはJetBrains CLionを使用して開発されています。JetBrains CLionをセットアップすることをお勧めします。
2. JetBrains CLionを開き、「ファイル」→「設定」→「プラグイン」を選択し、PlatformIO for CLionを検索してインストールします。
3. 「ファイル」→「バージョン管理からのプロジェクトのインポート」を選択し、このリポジトリのURLを選択してインポートします。
5. デバッグを容易にするために、Arduino IDEをインストールすることをお勧めします。

## 3. 実行
### 3.1 ハードウェア接続

このプロジェクトではXGZP040圧力センサーを使用し、これはボードに組み込まれたPCBモジュールです。VCC、GND、AOUTピンを接続するだけです。著者の接続は以下の通りです。

| Arduino Nano | XGZP040 |
| ------------ | ------- |
| 5V           | VCC     |
| GND          | GND     |
| A7           | AOUT    |

圧力センサーの実際の配線に応じて、電源およびデータ線を接続してください。

### 3.2 ソフトウェアの変更

コードの中心部分は **setup()**、**loop()**、**sendDataTask()** の3つの関数であり、複雑ではありません。

**setup()** はシリアルポートのボーレートを設定し、**loop()** は **sendDataTask()** を呼び出して遅延を行います。**sendDataTask()** は、標準化されたMIDI CC値の範囲で圧力センサーの値を読み取り、シリアルポート経由で送信します。

**getNext()** メソッドはデータを読み取り、MIDI CC値を返し、**mapper()** メソッドは力のカーブを処理します。

主な変更点は圧力センサーモジュールに関連しています。

#### 3.2.1 アナログ出力の圧力センサー

圧力センサーモジュールがアナログ出力の場合、**main.h**内の**ANALOG_IN**を接続したピンに変更します。次に、次のように **sendDataTask()** を変更し、書き込んでください。Arduino IDEを開き、デバイスを接続し、シリアルモニターを開き、ボーレートを115200（または **setup()** で指定した他の値）に設定して、吹いてArduino NanoのADC出力値の範囲を観察します。

```C++
void sendDataTask() {
    if (Serial) {
        DEBUG(analogRead(ANALOG_IN))
    }
}
```

出力値の範囲に応じて、**main.h**の**ADC_MIN**と**ADC_MAX**を調整してください。**mapper()** メソッドは力のカーブを処理します。他の力のカーブの形状が必要な場合、**mapper()** 内の式を変更できますが、このメソッドのコメントを注意深く読むことが重要です。

**サンプリングレートを変更したい場合**、**loop()** 内の **delay()** の値を変更します。Arduino Nanoの内部ADCの最高サンプリングレートは10kHzで、最小値は次のようになります。

```C++
delayMicroseconds(100);
```

#### 3.2.2 デジタル出力の圧力センサー

この部分はアイデアの説明のみです。

ほとんどのADCチップには、変換が完了し、サンプリング値を読み取ることができることを示すピンが1つあります。対応するピンに割り込みを設定して後続のタスクをトリガーできます。割り込みサービスルーチンは短くするべきですが、タスクフラグ+ポーリングの方法を使用できます。全体の構造は次のようになります。もちろん、FreeRTOSなどの組み込みオペレーティングシステムを使用してみることもできますが、まずはArduino Nanoがそれを処理できるかどうか分からないし、この種の単純なタスクには必要ありません。

```C++
// タスクフラグ
bool sendDataTaskFlag = false;

// あなたの割り込みサービスルーチン
void onInterruptTriggered() {
    // 短くする必要があるため、タスクフラグの設定のみ
    sendDataTaskFlag = true;
}

void setup() {
    // 割り込みを設定
    attachInterrupt(YOUR_PIN, onInterruptTriggered);
    // 他の設定を完了
}

void loop() {
    if (sendDataTaskFlag) {
        // タスクフラグをリセット
        sendDataTaskFlag = false;
        // タスクを実行
        sendDataTask();
    }
}
```

ADCチップの使用方法に関するマニュアルに従ってデータの読み取りドライバーを書きます（SPI、I2Cなどを使用する場合、Arduinoの組み込み関数を直接使用できます）。ADC入力を読み取る行の**normalized**の代わりに、**main.cpp**の**getNext()** の**analogRead(ANALOG_IN)** を変更してください。

### 3.3 Arduino Nanoへの書き込み

JetBrains CLionで、PlatformIOアイコンを見つけて（新しいUIの場合、右上にあります）、**Upload**をダブルクリックして書き込みを実行します。

### 3.4 お問い合わせ

質問やフィードバックがある場合は、[メール](mailto:aliothkry@proton.me)を送信してください。

## 4. 依存関係とオープンソースプロジェクトの宣言

このプロジェクトは、以下のオープンソースプロジェクトとツールを使用しています：

- [PlatformIO](https://platformio.org/): 組み込みシステム開発のためのクロスプラットフォーム開発ツール。
- [Arduino](https://www.arduino.cc/): 組み込みアプリケーションの構築に使用されるオープンソースのハードウェアおよびソフトウェアエコシステム。

これらのオープンソースプロジェクトにはそれぞれ独自のライセンス契約があります。詳細については、それぞれのプロジェクトのライセンス文書をご覧ください。

## 5. ライセンス契約

このプロジェクトは GNU GPL-v3 に従っています。詳細については、[LICENSE](LICENSE)ファイルを参照してください。

PlatformIOとArduinoなどのオープンソースコミュニティに感謝の意を表します。これらの優れたツールとリソースを提供していただきました。

<center><i>翻訳はChatGPTによって生成されました。</i></center>

