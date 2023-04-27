## Список компонентов

### Сервис авторизации
**API**:
-	Создание нового пользователя
      - входные параметры: login, пароль, имя, фамилия, email, дата рождения
      - выходные параметры: отсутствуют
-	Поиск пользователя по логину
     - входные параметры:  login
     - выходные параметры: имя, фамилия, email, дата рождения
-	Поиск пользователя по маске имени и фамилии
     - входные параметры: маска фамилии, маска имени
     - выходные параметры: login, имя, фамилия, email, дата рождения
-   Управление профилем пользователя
    - Входные параметры: ID пользователя
    - Выходные параметры: массив [фамилия, имя, почта, дата рождения]

### Сервис постов
**API**:
- Добавление записи на стену
  - Входные параметры: заголовок записи, пользователь, описание записи, содержание записи, дата создания
  - Выходные параметры: идентификатор записи
- Загрузка стены пользователя
  - Входнае параметры: идентификатор записи
  - Выходные парамтеры: заголовок записи, пользователь, описание, содержание поста, дата создания, комментарии
- Изменение поста
  - Входные параметры: идентификатор поста, заголовок поста, автор, описание поста, содержание поста, дата создания, комментарии
  - Выходные параметры: отсутствуют
- Просмотр комментариев поста
  - Входные параметры: идентификатор поста
  - Выходные параметры: комментарии поста
- Добавление комментариев к посту
  - Входные параметры: идентификатор поста
  - Выходные параметры: новый комментарий поста

### Сервис сообщений
**API**:
- Отправка сообщения пользователю
  - Входные параметры: ID отправителя, ID получателя
  - Выходные параметры: отсутствуют

- Получение списка сообщений для пользователя
  - Входные параметры: ID пользователя
  - Выходные параметры: массив [отправитель, получатель, сообщение]
  

  ### Сравнение скорости работы (10 секунд): 

| Количество потоков | Количество соединений | cache | no_cache |
|-------------------|-----------------------|-------|----------|
| 1                 | 1                     | 6538  | 5300     |
| 1                 | 10                    | 32719 | 2502     |
| 1                 | 100                   | 29757 | 2322     |
| 5                 | 10                    | 31584 | 2436     |
| 5                 | 100                   | 29841 | 2293     |
| 10                | 10                    | 31490 | 2417     |
| 10                | 100                   | 32350 | 2218     |
