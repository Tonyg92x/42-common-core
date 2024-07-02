<div id="top"></div>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->



<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://42.fr">
    <img src="images/42_Logo.svg.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">get_next_line</h3>

  <p align="center">
    Home made get_next_line function for c/c++ programming. Project of 42 cursus.
  </p>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#installation">Installation</a>
    </li>
    <li>
      <a href="#Corrections">Corrections</a>
    </li>
    <li>
      <a href="#Authors">Authors</a>
    </li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project

<p align="center">
  This is a project to read on a file the next line. You have to compile .c files with gcc and the tag -D BUFFER_SIZE=x where x is the buffer_size. The buffer size is the length of every read done. If it read the entire file, the program will read only one time and the rest of the file is saved in a static variable. The project is made to have a small amount of lines to be abble to write it again with ease on exam rank 02 of 42 cursus.
  
  EDIT : The malloc(tofuckingbig) is not a good practice. It is a version for the exam that dosent look at that. A cleaner version would be to realloc the right size when you need more space (dynamic allocation) or passing the retour variable in ft_strdup of my libft to trim it down to the actual size it needs and free retour.
  
 <!-- INSTALLATION -->
## Installation
```markdown
git clone git@github.com:Tonyg92x/42get_next_line.git
```
 
 <!-- CORRECTIONS -->
## Corrections
<p align="center">
  I used the Tripouille tester to validate my project: https://github.com/Tripouille/gnlTester

<!-- Authors -->
## Authors
<p align="left">
  Anthony Guay anthony.guay112@gmail.com
<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/anthony-g-75b27421b/
[product-screenshot]: images/screenshot.png
