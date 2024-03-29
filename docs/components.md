# Компонентная архитектура
<!-- Состав и взаимосвязи компонентов системы между собой и внешними системами с указанием протоколов, ключевые технологии, используемые для реализации компонентов.
Диаграмма контейнеров C4 и текстовое описание. 
-->
## Компонентная диаграмма

```plantuml
@startuml social_component
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

AddElementTag("microService", $shape=EightSidedShape(), $bgColor="CornflowerBlue", $fontColor="white", $legendText="microservice")
AddElementTag("storage", $shape=RoundedBoxShape(), $bgColor="lightSkyBlue", $fontColor="white")

Person(admin, "Администратор")
Person(moderator, "Модератор")
Person(user, "Пользователь")

System_Ext(web_site, "Клиентский веб-сайт", "HTML, CSS, JavaScript, React", "Веб-интерфейс")

System_Boundary(social_network, "Социальная сеть") {
   Container(web_site, "Клиентский веб-сайт", "React", "Клиентская часть социальной сети")
   Container(auth_service, "Сервис авторизации", "Node.js", "Сервис авторизации пользователей", $tags = "microService")    
   Container(user_service, "Сервис пользователей", "Node.js", "Сервис управления пользователями", $tags = "microService") 
   Container(post_service, "Сервис постов", "Node.js", "Сервис управления постами", $tags = "microService")   
   ContainerDb(db, "База данных", "PostgreSQL", "Хранение данных о пользователях, постах и комментариях", $tags = "storage")
}

Rel(admin, web_site, "Просмотр, добавление и редактирование информации о пользователях, постах и комментариях")
Rel(moderator, web_site, "Модерация контента и пользователей")
Rel(user, web_site, "Регистрация, просмотр информации о других пользователях, постах и комментариях")

Rel(web_site, auth_service, "Авторизация и аутентификация пользователей", "localhost/auth")
Rel(auth_service, db, "INSERT/SELECT/UPDATE", "SQL")

Rel(web_site, user_service, "Управление профилем пользователя", "localhost/user")
Rel(user_service, db, "INSERT/SELECT/UPDATE", "SQL")

Rel(web_site, post_service, "Управление постами", "localhost/posts")
Rel(post_service, db, "INSERT/SELECT/UPDATE", "SQL")
Rel(post_service, user_service, "Создание и просмотр постов", "localhost/user")

Rel(web_site, db, "SELECT", "SQL")

@enduml
```
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