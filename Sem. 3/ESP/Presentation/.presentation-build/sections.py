from pathlib import Path
from sys import argv
from uuid import uuid4
from zipfile import ZIP_DEFLATED, ZipFile

from lxml import etree


sections = [
    ("1  Entering Novigrad", 2),
    ("2  The scale of an open world", 1),
    ("3  Frustum culling", 3),
    ("4  Level of detail", 1),
    ("5  Collision detection", 2),
    ("6  Navigation and A*", 4),
    ("7  One encounter in Novigrad", 2),
]
p = "http://schemas.openxmlformats.org/presentationml/2006/main"
p14 = "http://schemas.microsoft.com/office/powerpoint/2010/main"
part = "ppt/presentation.xml"
source, destination = map(Path, argv[1:])

with ZipFile(source) as package:
    doc = etree.fromstring(package.read(part))
    ids = doc.xpath("./p:sldIdLst/p:sldId/@id", namespaces={"p": p})
    assert len(ids) == sum(size for _, size in sections)
    ext_list = doc.find(f"{{{p}}}extLst")
    if ext_list is None:
        ext_list = etree.SubElement(doc, f"{{{p}}}extLst")
    extension = etree.SubElement(ext_list, f"{{{p}}}ext", uri="{521415D9-36F7-43E2-AB2F-B90AF26B5E84}")
    section_list = etree.SubElement(extension, f"{{{p14}}}sectionLst", nsmap={"p14": p14})
    cursor = 0
    for name, size in sections:
        section = etree.SubElement(section_list, f"{{{p14}}}section", name=name, id="{" + str(uuid4()).upper() + "}")
        slide_ids = etree.SubElement(section, f"{{{p14}}}sldIdLst")
        for slide_id in ids[cursor:cursor + size]:
            etree.SubElement(slide_ids, f"{{{p14}}}sldId", id=slide_id)
        cursor += size

    with ZipFile(destination, "w", compression=ZIP_DEFLATED) as output:
        for name in package.namelist():
            content = etree.tostring(doc, encoding="UTF-8", xml_declaration=True) if name == part else package.read(name)
            output.writestr(name, content)
