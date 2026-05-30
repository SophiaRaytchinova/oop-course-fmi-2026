# Interface Segregation Principle

По-добре е да имаме няколко малки и конкретни интерфейса с по едно предназначение, вместо един голям интерфейс с няколко предназначения, който кара класовете да имплементират неща, които не използват.

С други думи: един клас не трябва да бъде принуждаван да има методи, които нямат смисъл за него.

---

## Проблемът

Нека имаме интерфейс `SmartDevice`, който съдържа методи за всякакви възможни smart устройства:

```cpp
class SmartDevice {
public:
    virtual ~SmartDevice() = default;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

    virtual void setTemperature(int degrees) = 0;
    virtual void recordVideo() = 0;
    virtual void playMusic() = 0;
};
```

На пръв поглед това изглежда удобно, защото всички устройства имат един общ интерфейс.

Проблемът е, че не всяко smart устройство може да прави всички тези неща.

Например:

- `SmartLight` може да се включва и изключва, но не може да пуска музика.
- `SmartThermostat` може да променя температура, но не може да записва видео.
- `SmartSpeaker` може да пуска музика, но не може да контролира температура.

Така класовете са принудени да имплементират методи, които не им трябват. Често това води до празни методи или до хвърляне на грешки като:

```cpp
throw std::runtime_error("This device does not support this feature");
```

Това е знак, че интерфейсът е твърде голям.

---

## По-добро решение

Вместо един голям интерфейс, разделяме поведението на малки интерфейси:

```cpp
class Switchable {
public:
    virtual ~Switchable() = default;

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
};

class TemperatureControllable {
public:
    virtual ~TemperatureControllable() = default;

    virtual void setTemperature(int degrees) = 0;
};

class VideoRecordable {
public:
    virtual ~VideoRecordable() = default;

    virtual void recordVideo() = 0;
};

class MusicPlayable {
public:
    virtual ~MusicPlayable() = default;

    virtual void playMusic() = 0;
};
```

Сега всеки клас имплементира само това, което реално поддържа.

Например:

```cpp
class SmartLight : public Switchable {
    // може само да се включва и изключва
};

class SmartThermostat : public Switchable, public TemperatureControllable {
    // може да се включва, изключва и да контролира температура
};

class SmartSpeaker : public Switchable, public MusicPlayable {
    // може да се включва, изключва и да пуска музика
};
```

Така кодът описва по-точно реалните възможности на обектите.

---

## Защо това е по-добре?

Когато интерфейсите са малки и конкретни:

- класовете не имплементират излишни методи
- има по-малко runtime грешки
- кодът става по-ясен
- класовете наследяват само тази функционалност, която реално им трябва
- промени в една функционалност не засягат несвързани класове

Например функция, която иска да пусне музика, не трябва да приема всяко smart устройство. Тя трябва да приема само обекти, които реално могат да пускат музика:

```cpp
void playSong(MusicPlayable& device) {
    device.playMusic();
}
```

Това прави кода по-безопасен, защото не можеш случайно да подадеш `SmartLight` на функция, която очаква музикално устройство.

---
