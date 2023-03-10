<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/42_Logo.svg.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Cub3d</h3>

  <p align="center">
    Video game Wolfstein 3D style
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
      <a href="#Authors">Authors</a>
    </li>
  </ol>
</details>

<!-- ABOUT THE PROJECT -->
## About The Project
<p>
The project is inspired by the Game wolfenstein 3D. It's a project in the 42 Qc school cursus. Wolfenstein was one of the first (if not) 3D game. It is not 3D tho... It is a 2D grid where you use ray casting to know the distance from the player to the next mesh. DDA algorithm is used to optimise the calculation of the ray length. I use a ray for each pixel of the width of the windows opened. For each ray I have a distance so I can use it to draw texture and render a 3D effect.<br/>
</p>

  <!-- INSTALLATION -->
## Installation
Use this command to clone the repository :
```markdown
git clone git@github.com:Tonyg92x/42cub3D.git
```
<p> For linux (deb), run sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev -y<br />
You can then make in the directory where there is the makefile to create the executable. <br/><br/>
On intel mac, brew install glfw3 and you should be good to go. It is not supported on mac m1</p>

<!-- Authors -->
## Authors
<p align="left">
  Anthony Guay anthony.guay112@gmail.com <br />
  Kampouse     https://github.com/Kampouse
<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/anthony-guay-75b27421b/
[product-screenshot]: images/screenshot.png
