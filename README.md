<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/42_Logo.svg.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">42-common-core projects</h3>

  <p align="center">
    The 42 common-core formation is a programming formation. In this formation, we learn c / c++ / vm / dockers / subnetting and web developpment. The project Born2BeRoot (secure linux vm creation) and netPractice (subnetting fundamentals) are not present since they don't require any code.
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#01-libft">libft</a>
    </li>
    <li>
      <a href="#02-printf">printf</a>
    </li>
    <li>
      <a href="#03-gnl">gnl</a>
    </li>
    <li>
      <a href="#04-push_swap">push_swap</a>
    </li>
    <li>
      <a href="#05-pipex">pipex</a>
    </li>
    <li>
      <a href="#06-so_long">so_long</a>
    </li>
    <li>
      <a href="#07-philosophers">philosophers</a>
    </li>
    <li>
      <a href="#08-minishell">minishell</a>
    </li>
    <li>
      <a href="#09-cub3d">cub3d</a>
    </li>
    <li>
      <a href="#10-piscineCPP">piscineCPP</a>
    </li>
    <li>
      <a href="#11-inception">inception</a>
    </li>
    <li>
      <a href="#12-irc">irc</a>
    </li>
    <li>
      <a href="#13-transcendence">transcendence</a>
    </li>
  </ol>
</details>

 <!-- 01-libft -->
## 01-libft
<p>
This is some fonctions from the c standard library. It is used afterward to do following projects.
</p>

<!-- 02-printf -->
## 02-printf
<p>
Printf is the print fonction in c. In this project, we use va_arg in to have multiple type and numbre of arguments possible in a fonction.
</p>

<!-- 03-gnl -->
## 03-gnl
<p>
Get next line read from a file the next line. In the project, we have to get an environnement variable to know the number of character's read. If the variable value is at 0, then we have to keep using the read fonction until we have the end of the line. If the variable value is higher then the line number of characters, the value of the read is store in a static variable to keep the information at the next gnl call. 
</p>

<!-- 04-push_swap -->
## 04-push_swap
<p>
Algorithm projet to sort some numbers in a stack memory container in an efficient way in some base parameters like movement avaible and number of pile memory container (2).
</p>

<!-- 05-pipex -->
## 05-pipex
<p>
First project where we execute some binary with execve fonction. We use pipe to communicate output of one binary file to the an other binary input. The bonus is to have conscutive pipe.
</p>

<!-- 06-so_long -->
## 06-so_long
<p>
2D graphical project using MLX visual library. MLX visual library use in the backend openGL. There is some map parsing on input and key press event, game loop and graphical rendering using premade fonctions to render it.
</p>

<!-- 07-philosophers -->
## 07-philosophers
<p>
Multi threading project. It's the classical philosopher exercise to learn the basic of controlling multi-threading in a program.
</p>

<!-- 08-minishell -->
## 08-minishell
<p>
This is a shell program to explore a unix operating system. The non bonus is limited to pipe operators. This project is like 70% parsing to understand the command input the right way and afterward (30 %) execute it the right way to have a behavior close to bash.
</p>

<!-- 09-cub3d -->
## 09-cub3d
<p>
This is a remake of the Wolfstein 3D game, which is the first FPS ever made. It is in 2D in the backend, but the rendering is in 3D. To do so, we use raycasting for every pixel (width) to know the distance between the player and obstacle's. With the value of the length of the ray, we can proceed to render the pixel to showcase the map to give a distance effect. Small math project, it was very fun. I enjoyed this one by not spoilling on how to do it from other projects from other students. The fun part was trying to understand the math behind it and code it in your'e own understanding. I learn at the end that I could use a better algorithm to optimise the length of the ray calculation. I used DDA algirithm so it could be efficient, but I understood late that the length of the ray for each x or y values stay the same after the first three iteration.
</p>

<!-- 10-piscineCPP -->
## 10-piscineCPP
<p>
This is a pricine for the CPP programing language. A Piscine is some project's done to learn a programming language.
</p>

<!-- 11-inception -->
## 11-inception
<p>
Docker project. We have to create our own image to make a small World Press project.
</p>

<!-- 12-irc -->
## 12-irc
<p>
IRC server. I loved this project. Unfortunatly I had only 2 weeks to do it so it had not received the loved it should have got. I have some plans to work on it in the future to optimise it, add encryption and file upload's. It really gave me some love for network programming.
</p>

<!-- 13-transcendence -->
## 13-transcendence
<p>
Full stack web application. 
</p>


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/anthony-guay-75b27421b/
[product-screenshot]: images/screenshot.png
