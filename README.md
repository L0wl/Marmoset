# Marmoset core

## Features
Reverse engineering of marmoset proprietary core, what allows you to view any 3d model, converted into .mview - see, how it looks in the store.

## Usage
Go to [ArtStation](https://www.artstation.com/search?sort_by=relevance&asset_types_include=marmoset), select any model, what you want (Marmoset viewer asset type is already applied)
Open developer (**F12**) Go to Elements and search (**Ctrl**+**F**) and search something like ".mview". Embed viewer link starts from `https://cdna.artstation.com/p/assets/marmosets/...`
Open that link in the new tab and downloading of mview file already running.

Buffers now can be vizualized only through manual WebGL mapping, but soon it's come possible to be exported into open 3d formats like `Collada`, `Blender`

Common mesh buffers are named as `mesh*.dat`

## TODO
- [x] .dat file support
- [x] .mview partially support
- [x] Detecting MIME-types
- [x] Extracting mesh data (e.g: Vertices, Indices and faces)
- [x] Extracting texture maps
- [x] Creating material bindings and texture map bindings (mtl library)
- [x] Normal data extraction
- [x] Extracting of scene outliner
- [ ] Data export layer
- [ ] Multi format representation
- [ ] Signature checking and buffer validation
- [ ] Skinning weights readable format
- [ ] Animation tracks and framerate interpolator
- [ ] Preview data generation
