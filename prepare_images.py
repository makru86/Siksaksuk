import os
from PIL import Image

for f in os.listdir('download'):
    im = Image.open(os.path.join('download', f))
    width, height = im.size
    
    filename = os.path.splitext(f[49:])[0]
    
    ldst = os.path.join('res', filename + '_l.png')
    im.crop((0, 0, width/2, height)).convert('RGBA').save(ldst)

    rdst = os.path.join('res', filename + '_r.png')
    im.crop((width/2, 0, width, height)).convert('RGBA').save(rdst)


