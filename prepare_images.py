import os
from PIL import Image

d = 'res'
for filename in os.listdir(d):
    src = os.path.join(d, filename)
    im = Image.open(src)
    width, height = im.size

    ldst = os.path.join(d, os.path.splitext(filename)[0] + '_l' + '.png')
    lim = im.crop((0, 0, width/2, height))
    lim.save(ldst)

    rdst = os.path.join(d, os.path.splitext(filename)[0] + '_r' + '.png')
    rim = im.crop((width/2, 0, width, height))
    rim.save(rdst)


