
# Links
* [gnuplot demo script: pm3dcolors.dem](http://gnuplot.sourceforge.net/demo/pm3dcolors.html)
* [gnuplot palletes](https://github.com/Gnuplotting/gnuplot-palettes)
## python colormaps
* [python colormaps](http://www-personal.umich.edu/~mejn/computational-physics/colormaps.py)
* https://gitlab.kitware.com/paraview/paraview/blob/master/Wrapping%2FPython%2Fparaview%2F_colorMaps.py
* https://github.com/BIDS/colormap/blob/master/colormaps.py
* https://sciviscolor.org/resources/
## People
* (Kenneth Moreland)[http://www.kennethmoreland.com/]
* (Colin Ware)[https://ccom.unh.edu/vislab/colin_ware.html]
* (Peter Kovesi)[https://www.peterkovesi.com/]
## www
* (khan academy:  color science by Pixar)[https://www.khanacademy.org/partner-content/pixar/color]

## Lightness
* (How to Determine Lightness by Reda Lemeden)[https://thoughtbot.com/blog/closer-look-color-lightness#how-to-determine-lightness]
* (stackoverflow question: formula-to-determine-brightness-of-rgb-color)[https://stackoverflow.com/questions/596216/formula-to-determine-brightness-of-rgb-color]


(Relative luminance is formed as a weighted sum of linear RGB components)[https://en.wikipedia.org/wiki/Luma_(video)]

`$Y = 0.2126 R + 0.7152 G + 0.0722 B$`


# gradient forms:
* table
  * array of 3 values ( RGB)
* function ( 3 transfer functions) = colour map 
* image
  * stripe of colors
  * diagram of the function
  * [CLUT image](https://imagemagick.org/script/command-line-options.php#clut): image is ordinarily a gradient image containing the histogram mapping of how each channel should be modified. Typically it is a either a single row or column image of replacement color values. If larger than a single row or column, values are taken from a diagonal line from top-left to bottom-right corners.



# Taxonomy of color gradients


(A Taxonomy of Colour Maps by Peter Kovesi)[http://arxiv.org/abs/1509.03700]
* linear : are intended for general use and have colour lightness values that increase or decrease linearly over the colour map's range
* diverging
* rainbow
* cyclic
* isoluminant










# Motivation

Show how to implement color gradient in your program ( C)







## Contributors

are wellcome 


  
## License

A short snippet describing the license (MIT, Apache, etc.)


# technical notes
GitLab uses:
* the Redcarpet Ruby library for [Markdown processing](https://gitlab.com/gitlab-org/gitlab-foss/blob/master/doc/user/markdown.md)
* KaTeX to render [math written with the LaTeX syntax](https://gitlab.com/gitlab-org/gitlab-foss/blob/master/doc/user/markdown.md), but [only subset](https://khan.github.io/KaTeX/function-support.html)

## API Reference

simple one file c programs which 
- do not need any extra libraries 
- can be run from console
- compiled with gcc 
- multiplatform

How to compile and run is described in the comments of c files


## Git


```git
cd existing_folder
git init
git remote add origin git@gitlab.com:adammajewski/color_gradient.git
git add .
git commit -m "Initial commit"
git push -u origin master
```



```
  git clone git@gitlab.com:adammajewski/color_gradient.git
```


local repo : ~/c/varia/color/gradient

