# Пример за Command pattern - BankAccountsApplication

Примерът представлява малко конзолно банково приложение, в което потребителят въвежда текстови команди за изпълнение на различни операции. Всяка операция е представена чрез отделен command клас, а `CommandFactory` създава правилната команда според въведения текст и аргументите към него. **Приложението е непълно и служи главно за пример за Command pattern.**

> Части от работата с файлове и пълната бизнес логика са оставени без реална имплементация, за да се фокусира примерът върху Command pattern.

Поддържани команди:

```text
login <username> <password>
logout
deposit <amount>
withdraw <amount>
transfer <recipient> <amount>
balance
help
exit
```

Пример:

```text
login alice pass
deposit 100
transfer bob 50
balance
logout
exit
```

