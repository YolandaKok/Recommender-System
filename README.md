# Recommender System

## Clustering

* Compile Command: **make** **cluster**
* Execution Command: **. /cluster** -i < input_file > -c < configuration_file > -o < output_file > -d < metric >

* metric: **euclidean** or **cosine**

- For instance: . /cluster -i datasets/twitter_dataset_small_v2.csv -c datasets/cluster.conf -o out.txt -d euclidean

## Recommendation

* Compile Command: **make** **recommendation**
