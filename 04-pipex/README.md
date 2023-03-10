<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/42_Logo.svg.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Pipex</h3>

  <p align="center">
    42 Project of 42 cursus
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

<p align="left">
  Program that need to do the equivalent of "< file1 cmd1 | cmd2 > file2" on taking arguments like that : ./pipex file1 cmd1 cmd2 file2. Basically, you take what is in file1, and use it as an entry for the command 1. Then the output of command 1 fo as the entry of cmd2, until there is no command left then send the output of it into the file at the end. If the file1 dosen't exist, don't run the program. If the last file dosen't exist, create it. If it does exist, replace its content with the output.
  

  <!-- INSTALLATION -->
## Installation
Use this command to clone the repository :
```markdown
git clone git@github.com:Tonyg92x/42Pipex.git
```
Then you can go in the folder and write the command "make" to compile the library and everything needed for the program. The executable is named pipex. You can test the program using "./pipex x cmd cmd cmd y" where x is the file that is taken as first entry and y the file that the will contain the output. cmd are any command that you can use in your unix environnement.
 
<!-- Authors -->
## Authors
<p align="left">
  Anthony Guay anthony.guay112@gmail.com
<p align="right">(<a href="#top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/anthony-guay-75b27421b/
[product-screenshot]: images/screenshot.png
