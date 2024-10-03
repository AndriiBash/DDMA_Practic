<?php
// Запрішуємо безпосередньо використовувати Joomla API
defined('_JEXEC') or die;

// Функція, яка виводить "Hello world" на сторінці сайту
function modHelloWorld()
{
    echo "Hello, its module Lab5!";
}

// Виконуємо функцію, коли модуль відображається на сторінці
modHelloWorld();
?>

