<div id="top"></div>

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/42_Logo.svg.png" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">Push Swap</h3>

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
  The project is about sorting integers with a given set of instruction. The instructions are : <br><br>
  <B>swap a (sa) :</b> Swap the first 2 elements at the top of stack a.<br>
  <B>swap b (sb) :</b> Swap the first 2 elements at the top of stack b.<br>
  <B>swap a&b (ss) : </b> Swap the first 2 elements at the top of both lists.<br>
  <B>push a (pa) : </b> Take the first element of the list b and put it at the top of the list a<br>
  <B>push b (pb) : </b> Take the first element of the list a and put it at the top of the list b<br>
  <B>rotate a (ra) : </b> Shift up all elements of stack a by 1. The first element become the last one.<br>
  <B>rotate b (rb) : </b> Shift up all elements of stack b by 1. The first element become the last one.<br>
  <B>rotate a&b (rr) : </b> Do ra and rb.<br>
  <B>reverse rotate a (rra) : </b> Shift down all elements of stack a by 1. The last element become the first one.<br>
  <B>reverse rotate b (rrb) : </b> Shift down all elements of stack b by 1. The last element become the first one.<br>
  <B>reverse rotate a&b (rrr) : </b> Do rra and rrb.<br><br>
  
  You have to sort any number of elements in the smallest number of operations possible. You can enter arguments in one string separated by a space, or enter multiple arguments. If you enter two times the same number, the program return an error. If any arguments are higher or lower then int limit, return an error and finally if any argument contain a letter return an error. The program display every operation to sort the arguments passed, split by \n.
  

  <!-- INSTALLATION -->
## Installation
Use this command to clone the repository :
```markdown
git clone git@github.com:Tonyg92x/42Push_swap.git
```
Then you can go in the folder and write the command "make" to compile the library and everything needed for the program. The executable is named push_swap. You can test the program using "./push_swap x" where x is the argument. The program will display all operation needed to sort the arguments passed.
 
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
