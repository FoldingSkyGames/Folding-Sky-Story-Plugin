# Folding Sky Story Plugin

The Folding Sky Story Plugin is an additional set of blueprint nodes for narrative flow control being lazily developed in UE 4.26

* Uses standard blueprints familiar to any new UE4 developer
* 6 new powerful blueprint nodes
* An event system for utilization of data arranged on the blueprint graph
* Can use localized text, string tables, or Dialogue Wave assets
* Text based choices allow for narrative style control over blueprint flow


## Usage

1. Create a Story Blueprint from the "Create Advanced Asset -> Blueprints" context menu in editor
<p align="center">
  <img src="./GitAssets/CreateStoryBlueprint.jpg" alt="Create Story Blueprint">
</p>
2. Build a graph using "Story Nodes" and supply them with data
<p align="center">
  <img src="./GitAssets/MakeStoryNodes.jpg" alt="Author Story Graph">
</p>
3. Use the event "On Story Posted" to handle data you have arranged by using story nodes
   This is good for visualization of Text or playing of audio set up in Dialogue Waves
<p align="center">
  <img src="./GitAssets/OnStoryPosted.jpg" alt="Handle On Story Posted">
</p>
4. **Have fun!**