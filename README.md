# LAB13

Цель: освоить принципы работы с хеш-таблицами и двусвязными списками.

Задача: написать программу поиска с кэшем.

Условия:
Программа должна выполнять поиск IP адреса по доменному имени в файле, содержащем DNS таблицу. Поиск необходимо реализовать через кэш с алгоритмом LRU.

1) Пользователь задает доменное имя.
2) Программа проверяет наличие данных в кэше:
a. если HIT (присутствует в кэше) – возвращает IP адрес пользователю.
b. если MISS (отсутствует в кэше) – программа производит поиск по файлу, помещает запись в кэш и возвращает IP адрес. 

Кэш должен содержать значения <key, value>, где k – это доменное имя, а v – IP адрес. Данные в кэш помещаются по алгоритму LRU. 

SONARCLOUD - https://sonarcloud.io/project/overview?id=Oleg200447_LAB13
