# Контекст решения
<!-- Окружение системы (роли, участники, внешние системы) и связи системы с ним. Диаграмма контекста C4 и текстовое описание. 
-->
```plantuml
@startuml
!include https://raw.githubusercontent.com/plantuml-stdlib/C4-PlantUML/master/C4_Container.puml

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
## Назначение систем
|Система| Описание|
|-------|---------|
| Социальная сеть | Веб-интерфейс, обеспечивающий доступ к информации о других пользователях, их стене и обмену информацией между ними. Бэкенд сервиса реализован в виде микросервисной архитектуры |
