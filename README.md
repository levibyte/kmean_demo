# kmean_demo
The question is following: Given number K and some data, classify and put data into K buckets.

This is silly atempt to address this question by implementing k-means algorithm, the most basic classification algorithm. For simplicty and visbility reasons I've choosen data to be 2d points on the surface.

Overall algorithm's yield is **very much** depends on data distribution ( are they allready "split" into K buckets or spread randomly?) and on the choice of first pivot points. Therfore on some occasions it can split data ideally but next time it can be completly wrong.


### Run examples

*Left:* raw data, *Right:* after classification to buckets ( via color )

<img src="https://i.ibb.co/WtHJXg6/kmeans3.png" width="390" height="500"> <img src="https://i.ibb.co/4777pTb/kmeans4.png" width="390" height="500">


Same, but for larger gravity values: 

<img src="https://i.ibb.co/QdN6s8s/kmeans-1.png" width="390" height="500"> <img src="https://i.ibb.co/jrXx4YX/kmeans2.png" width="390" height="500">

Fail case: 

<img src="https://i.ibb.co/wd3WdYL/kmeans5.png" width="390" height="500"> <img src="https://i.ibb.co/ssfwrW6/kmeans6.png" width="390" height="500">



