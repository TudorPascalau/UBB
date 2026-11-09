import fs from "node:fs/promises";
import { constants as fsConstants } from "node:fs";
import { spawnSync } from "node:child_process";
import path from "node:path";
import { fileURLToPath, pathToFileURL } from "node:url";
import { Presentation, PresentationFile, FileBlob } from "file:///C:/Users/tudor/.cache/codex-runtimes/codex-primary-runtime/dependencies/node/node_modules/@oai/artifact-tool/dist/artifact_tool.mjs";

const build = path.dirname(fileURLToPath(import.meta.url));
const root = path.dirname(build);
const skill = "C:/Users/tudor/.codex/plugins/cache/openai-primary-runtime/presentations/26.1105.12137/skills/presentations";
const python = "C:/Users/tudor/.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe";
const script = JSON.parse(await fs.readFile(path.join(build, "script.json"), "utf8"));
const deck = Presentation.create({ slideSize: { width: 1280, height: 720 } });
const W = 1280, H = 720;
const C = {
  paper: "#F4F0E7", ink: "#1F2825", muted: "#50605A", charcoal: "#14221F",
  white: "#FFFAEF", amber: "#EBC378", brown: "#79531C", rust: "#A7472F",
  green: "#1F634E", pale: "#DCEAE1", map: "#EAE8DB", road: "#F7F3E8",
  grid: "#C8CDC2", wall: "#46534F", moss: "#AEC9B6", lightRust: "#F3E1D8",
};
const font = "Segoe UI";
const SRC = {
  city: "https://www.gamepro.de/galerien/the_witcher_wild_hunt,99471.html",
  gate: "https://x.com/thewitcher/status/1615363448505786368",
  gameplay: "https://www.youtube.com/watch?v=xx8kQ4s5hCY",
  gdc: "https://media.gdcvault.com/GDC2014/Presentations/Bushnaief_Jasin_Solving_Visibility_In.pdf",
  frustum: "https://dev.epicgames.com/documentation/en-us/unreal-engine/visibility-and-occlusion-culling-in-unreal-engine",
  foliage: "https://www.nvidia.com/en-us/geforce/news/the-witcher-3-wild-hunt-graphics-performance-and-tweaking-guide/#foliagevisibilityrange",
  lod: "https://dev.epicgames.com/documentation/en-us/unreal-engine/optimizing-lod-screen-size-per-platform-in-unreal-engine",
  collision: "https://box2d.org/doc_version_2_4/md__e_1_2github_2box2d__24_2docs_2collision.html",
  nav: "https://cdprojektred.atlassian.net/wiki/spaces/W3REDkit/pages/16351233",
  astar: "https://ai.stanford.edu/~nilsson/OnlinePubs-Nils/PublishedPapers/astar.pdf",
  rose: "https://www.tobiasgarpenhall.com/rose",
  azure: "https://assetstore.unity.com/packages/3d/vegetation/azure-nature-167725",
  graphfinder: "https://graphfinder.github.io/visualization/#animate_grid-watch-the-search-explore",
};
const none = { fill: "none", width: 0 };
const pos = (left, top, width, height) => ({ left, top, width, height });
const stroke = (fill, width) => ({ style: "solid", fill, width });

function text(slide, value, x, y, w, h, options = {}) {
  const { size = 28, color = C.ink, bold = false, align = "left", link } = options;
  const box = slide.shapes.add({
    geometry: "textbox", name: value.replaceAll("\n", " ").slice(0, 70),
    position: pos(x, y, w, h), fill: "none", line: none,
    ...(link ? { hyperlink: { uri: link, isExternal: true } } : {}),
  });
  box.text = value;
  box.text.style = {
    typeface: font, fontSize: size, color, bold, alignment: align,
    verticalAlignment: "middle", autoFit: "none", wrap: "none", insets: 0,
  };
  return box;
}

function shape(slide, name, geometry, x, y, w, h, fill, outline = "none", width = 0) {
  return slide.shapes.add({
    name, geometry, position: pos(x, y, w, h), fill, line: stroke(outline, width),
  });
}
const rect = (s, n, x, y, w, h, fill, line, sw) => shape(s, n, "rect", x, y, w, h, fill, line, sw);
const dot = (s, n, x, y, d, fill, line, sw) => shape(s, n, "ellipse", x-d/2, y-d/2, d, d, fill, line, sw);
function pathShape(slide, name, points, { fill = "none", line = "none", width = 0, closed = false } = {}) {
  const x = Math.min(...points.map(p => p[0])), y = Math.min(...points.map(p => p[1]));
  const w = Math.max(1, Math.max(...points.map(p => p[0])) - x);
  const h = Math.max(1, Math.max(...points.map(p => p[1])) - y);
  const commands = points.map(([px, py], i) => ({ [i ? "lineTo" : "moveTo"]: { x: px-x, y: py-y } }));
  if (closed) commands.push({ close: {} });
  return slide.shapes.add({
    name, geometry: "custom", position: pos(x, y, w, h), fill, line: stroke(line, width),
    customPaths: [{ width: w, height: h, commands }],
  });
}
const line = (s, n, pts, color, width = 2) => pathShape(s, n, pts, { line: color, width });
const poly = (s, n, pts, fill, outline = "none", width = 0) =>
  pathShape(s, n, pts, { fill, line: outline, width, closed: true });

function arrow(s, name, from, to, color, width = 4) {
  line(s, name, [from, to], color, width);
  const a = Math.atan2(to[1]-from[1], to[0]-from[0]);
  const head = 12;
  const left = [to[0]-head*Math.cos(a)+head*0.55*Math.sin(a), to[1]-head*Math.sin(a)-head*0.55*Math.cos(a)];
  const right = [to[0]-head*Math.cos(a)-head*0.55*Math.sin(a), to[1]-head*Math.sin(a)+head*0.55*Math.cos(a)];
  poly(s, `${name} arrowhead`, [to, left, right], color);
}

async function photo(slide, file, alt, x, y, w, h) {
  const b = await fs.readFile(path.join(build, file));
  slide.images.add({ name: file, blob: b.buffer.slice(b.byteOffset, b.byteOffset+b.byteLength),
    contentType: file.endsWith(".gif") ? "image/gif" : "image/jpeg",
    alt, fit: "cover", position: pos(x,y,w,h) });
}
const frame = (label, title, dark = false) => {
  const s = deck.slides.add();
  s.background.fill = dark ? C.charcoal : C.paper;
  if (label) text(s, label.toUpperCase(), 62, 35, 900, 25,
    { size: 17, color: dark ? C.amber : C.brown, bold: true });
  if (title) text(s, title, 62, 72, 1160, 66,
    { size: 52, color: dark ? C.white : C.ink, bold: true });
  return s;
};
const folio = (s, n, caption, dark = false) => {
  const color = dark ? "#D3DDD5" : C.muted;
  if (caption) text(s, caption, 62, 660, 1090, 25, { size: 16, color });
  text(s, String(n).padStart(2,"0"), 1160, 660, 58, 25, { size: 16, color, align:"right" });
};
function notes(s, who, section, range, sources, overrides = {}) {
  const paragraphs = range ? script.slice(range[0], range[1]).map((p,i) => overrides[i] ?? p.trim()) : [];
  s.speakerNotes.text = [
    who && `${who}  |  ${section}`,
    ...paragraphs,
    sources?.length && "Sources\n" + sources.join("\n"),
  ].filter(Boolean).join("\n\n");
}
function rule(s, head, body, x, y, w = 430) {
  text(s, head, x,y,w,38,{ size: 29,bold:true });
  text(s, body, x,y+43,w,72,{ size: 24,color:C.muted });
}
function gateMap(s, rotated) {
  rect(s,"Top-down map", 548,174,666,442,C.map);
  rect(s,"Road toward city",654,194,173,402,C.road);
  rect(s,"Road toward gate",654,274,540,111,C.road);
  const origin=[741,533];
  const theta=rotated ? 50*Math.PI/180 : 0;
  const turn=([x,y])=>[
    origin[0]+x*Math.cos(theta)-y*Math.sin(theta),
    origin[1]+x*Math.sin(theta)+y*Math.cos(theta),
  ];
  const points = [[-26,-44],[26,-44],[145,-350],[-145,-350]].map(turn);
  poly(s,"Camera viewing area",points,C.moss,C.green,3);
  rect(s,"Left section of city wall",887,278,62,21,C.wall);
  rect(s,"Right section of city wall",1008,278,186,21,C.wall);
  rect(s,"Gate left pillar",945,272,14,33,C.wall);
  rect(s,"Gate right pillar",999,272,14,33,C.wall);
  text(s,"Gate",941,210,72,29,{size:21,bold:true,align:"center"});
  const guardColor=rotated?C.green:C.rust;
  rect(s,"Guard bounding box",965,309,51,51,"none",guardColor,3);
  dot(s,"Guard",990,335,20,guardColor);
  text(s,"Guard",1060,325,92,25,{size:19,bold:true});
  dot(s,"Camera position",...origin,24,C.charcoal,C.paper,3);
  arrow(s,"Camera direction",turn([0,-12]),turn([0,-58]),C.charcoal,3);
  text(s,"Camera",692,554,98,27,{size:20,bold:true,align:"center"});
  text(s,"View frustum",rotated?850:668,rotated?377:347,157,28,{size:21,bold:true,align:"center"});
}

// 01 — Title and audience opening
{
  const s=deck.slides.add();
  s.background.fill=C.charcoal;
  await photo(s,"novigrad-crop.jpg","Geralt on horseback overlooking Novigrad",551,0,729,H);
  rect(s,"Title panel",0,0,553,H,C.charcoal);
  text(s,"ENGLISH FOR COMPUTER SCIENCE",62,86,475,28,{size:17,color:C.amber,bold:true});
  text(s,"Algorithms and\nTechniques in\nVideo Game\nOptimization",60,165,496,304,
    {size:63,color:C.white,bold:true});
  text(s,"A case study from The Witcher 3: Wild Hunt",62,516,485,40,{size:24,color:"#E3E9E0"});
  notes(s,"Speaker 1","Section 1 · 0:00–1:45",[9,11],[`Novigrad gameplay still · GamePro / CD Projekt Red · ${SRC.city}`]);
}

// 02 — Establish the shared scene before the diagrams
{
  const s=frame("Entering Novigrad","At the city gate");
  await photo(s,"gate-official.jpg","Geralt rides toward the walls and gate of Novigrad",62,163,733,412);
  const prompts=[
    ["Rendering","When should we draw\nthe guard?"],
    ["Collision detection","What stops him at\na wall?"],
    ["Pathfinding","How could he get\naround it?"],
  ];
  prompts.forEach(([head,body],i)=>rule(s,head,body,845,164+i*135,360));
  folio(s,2,"Gameplay still · CD Projekt Red");
  notes(s,"Speaker 1","Section 1 · continued",[11,13],[`Gameplay still · CD Projekt Red · ${SRC.gate}`,SRC.gameplay],{
    0: script[11].replace("the main capital city of the game","a major city in the game"),
  });
}

// 03 — Documented measurements
{
  const s=frame("Rendering at scale","A visibility test in The Witcher 3",true);
  text(s,"One development scene, one viewpoint",62,154,1140,42,{size:28,color:"#D3DDD5"});
  const metrics=[
    [62,"62,000+","pieces of static\ngeometry in the scene"],
    [462,"<500","pieces visible from\nthe test viewpoint"],
    [866,"61 MB","of precomputed\nvisibility data loaded"],
  ];
  for(const [x,num,desc] of metrics){
    text(s,num,x,260,360,103,{size:86,color:C.amber,bold:true});
    line(s,"Metric divider",[[x,381],[x+317,381]],"#688079",1.5);
    text(s,desc,x,409,359,90,{size:30,color:C.white});
  }
  folio(s,3,"Source · CD Projekt Red and Umbra, GDC 2014",true);
  notes(s,"Speaker 1","Section 2 · 1:45–2:30",[21,24],[SRC.gdc],{
    1: script[22].trim()+" The test also loaded sixty-one megabytes of precomputed visibility data.",
  });
}

// 04 and 05 — Same map and camera position, different headings
{
  const s=frame("Frustum culling","The guard is outside the camera’s view");
  rule(s,"View frustum","The 3D volume the camera\ncan see.",62,181);
  rule(s,"Bounding box","A simple box enclosing\nthe guard.",62,306);
  text(s,"Entirely outside → skip drawing",62,493,465,45,{size:27,bold:true,color:C.rust});
  gateMap(s,false);
  folio(s,4,"Simplified overhead view of the gate");
  notes(s,"Speaker 1","Section 3 · 2:30–5:15",[30,33],[SRC.frustum]);
}
{
  const s=frame("Frustum culling","The camera turns toward the gate");
  rule(s,"Same guard, same position","Only the camera direction\nhas changed.",62,181);
  rule(s,"The box enters the frustum","The renderer keeps the guard\nas a candidate for drawing.",62,306);
  text(s,"Intersects the view → keep testing",62,493,476,45,{size:27,bold:true,color:C.green});
  gateMap(s,true);
  folio(s,5,"Simplified overhead view of the gate");
  notes(s,"Speaker 1","Section 3 · continued",[33,35],[SRC.frustum],{
    1: script[34].replace("Now that we’re looking at the gate, there’s a second decision to make. How much detail can we actually see from here?",
      "Here’s what that same test looks like in a running game engine."),
  });
}

// 06 — Recorded engine debug view
{
  const s=frame("Frustum culling","Frustum culling in a running engine");
  await photo(s,"frustum-demo.gif","R.O.S.E. engine debug view showing groups of trees and rocks culled as the view frustum changes",62,166,857,444);
  rule(s,"Camera frustum","The white outline marks\nthe viewing volume.",949,182,275);
  rule(s,"Watch the scenery","Trees and rocks drop out\nas the view moves away.",949,363,275);
  folio(s,6,"Engine debug capture · Tobias Garpenhall, R.O.S.E.");
  s.speakerNotes.text = [
    "Speaker 1  |  Section 3 · continued",
    "This is a debug view of the R.O.S.E. engine. Watch the group of trees and rocks as the camera view moves. The engine skips groups that fall outside its frustum.",
    "Once something is in view, the engine still has to decide how much detail to draw.",
    `Source · Tobias Garpenhall, R.O.S.E. · ${SRC.rose}\nCapture resized and frame-sampled for playback.`,
  ].join("\n\n");
}

// 07 — Real game asset models at equal size
{
  const s=frame("Level of detail","One tree at three levels of detail");
  text(s,"Use a simpler mesh when the tree takes up less screen space.",62,153,1150,42,{size:28,color:C.muted});
  await photo(s,"azure-models.jpg","Rendered AZURE Nature tree asset at LOD0, LOD1 and LOD2",192,208,896,371);
  const levels=[[378,"LOD 0","4,918 triangles"],[633,"LOD 1","2,834 triangles"],[886,"LOD 2","1,494 triangles"]];
  for(const [x,level,count] of levels){
    text(s,level,x-105,589,210,32,{size:25,bold:true,align:"center"});
    text(s,count,x-105,621,210,29,{size:21,color:C.muted,align:"center"});
  }
  folio(s,7,"AZURE Nature tree asset shown at equal size · Raygeas / Unity Asset Store");
  notes(s,"Speaker 1","Section 4 · 5:15–7:00",[42,46],[SRC.foliage,SRC.lod,SRC.azure],{
    1: script[43] + " Here the same game asset is shown at three levels. The most detailed version has nearly five thousand triangles. The simplest has about fifteen hundred.",
  });
}

// 07 — Colliders 
{
  const s=frame("Collision detection","The shapes that stop a character");
  rule(s,"Collider","A simple shape used to\ntest for contact.",62,194);
  rule(s,"Character and wall","A capsule and a box can\nrepresent solid objects.",62,336);
  rect(s,"Collision diagram field",553,175,663,418,C.map);
  line(s,"Ground plane",[[607,507],[1161,507]],"#84968E",2);
  const capsule = shape(s,"Character capsule","roundRect",681,271,115,236,C.moss,C.green,4);
  capsule.borderRadius=57;
  rect(s,"Wall collider",938,225,162,282,"#CDD1C9",C.wall,4);
  arrow(s,"Intended movement",[810,390],[921,390],C.rust,5);
  text(s,"Capsule",674,526,131,29,{size:22,color:C.green,bold:true,align:"center"});
  text(s,"Wall box",937,526,165,29,{size:22,color:C.wall,bold:true,align:"center"});
  folio(s,8,"Illustrative collision shapes at the gate");
  notes(s,"Speaker 2","Section 5 · 7:00–10:00",[54,56],[SRC.collision]);
}

// 08 — Spatial grid and two stages
{
  const s=frame("Collision detection","Broad phase and narrow phase");
  rule(s,"Broad phase","Find objects that could collide\nwith the guard.",62,184);
  rule(s,"Narrow phase","Test the candidate shapes\nfor actual contact.",62,317);
  text(s,"100 objects → 4,950 possible pairs",62,505,480,43,{size:26,color:C.brown,bold:true});
  const x=572,y=199,k=84, cols=7,rows=4;
  rect(s,"Collision grid",x,y,k*cols,k*rows,C.road);
  for(const [cx,cy] of [[1,2],[2,2],[3,2],[3,1],[2,1]]){
    rect(s,"Candidate area",x+cx*k,y+cy*k,k,k,C.pale);
  }
  for(let i=0;i<=cols;i++)line(s,"Grid column",[[x+i*k,y],[x+i*k,y+k*rows]],C.grid,1.5);
  for(let i=0;i<=rows;i++)line(s,"Grid row",[[x,y+i*k],[x+k*cols,y+i*k]],C.grid,1.5);
  rect(s,"Wall candidate",x+3*k+40,y+k+5,20,2*k-10,C.wall);
  dot(s,"Guard position",x+1.5*k,y+2.5*k,29,C.green);
  arrow(s,"Guard movement",[x+1.77*k,y+2.5*k],[x+2.84*k,y+2.5*k],C.green,4);
  dot(s,"Barrel candidate",x+2.55*k,y+1.49*k,29,"#A46737");
  rect(s,"Distant cart",x+5.2*k,y+2.25*k,48,42,"#9BA8A2");
  text(s,"Guard",x+0.78*k,y+2.69*k,120,25,{size:18,bold:true,align:"center"});
  text(s,"Barrel",x+1.94*k,y+1.68*k,105,23,{size:18,bold:true,align:"center"});
  text(s,"Wall",x+3*k+8,y-29,84,23,{size:18,bold:true,align:"center"});
  text(s,"Cart",x+4.97*k,y+2.69*k,85,23,{size:18,color:C.muted,align:"center"});
  text(s,"Highlighted cells contain possible collisions.",572,551,620,34,{size:23,color:C.muted});
  folio(s,9,"Illustrative spatial grid");
  notes(s,"Speaker 2","Section 5 · continued",[56,60],[SRC.collision]);
}

// Shared gate diagram for the navigation mesh and grid.
const map = { x:600,y:181,k:77,cols:7,rows:5 };
const center = (col,row) => [map.x+(col+0.5)*map.k,map.y+(row+0.5)*map.k];
function mapBase(s, grid) {
  const { x,y,k,cols,rows }=map;
  rect(s,"Gate map area",x,y,k*cols,k*rows,C.road);
  if(grid){
    for(let i=0;i<=cols;i++)line(s,"Grid column",[[x+i*k,y],[x+i*k,y+k*rows]],C.grid,1.5);
    for(let i=0;i<=rows;i++)line(s,"Grid row",[[x,y+i*k],[x+k*cols,y+i*k]],C.grid,1.5);
  } else {
    const areas=[[[3,0],[4,0],[4,1],[3,1]]];
    for(const [left,right] of [[0,3],[4,7]]){
      for(const [top,bottom] of [[0,1],[1,2],[2,5]]){
        areas.push([[left,top],[right,top],[right,bottom],[left,bottom]]);
      }
    }
    for (const area of areas) {
      const pts=area.map(([col,row])=>[x+col*k,y+row*k]);
      poly(s,"Walkable polygon",pts,C.pale,C.green,1.8);
      line(s,"Navigation triangle edge",[pts[0],pts[2]],"#7EAA93",1.8);
    }
    line(s,"Walkable connection",[[x+3*k,y],[x+3*k,y+k]],"#7EAA93",1.8);
  }
  rect(s,"Blocked wall",x+3*k,y+k,k,4*k,C.wall);
  text(s,"Wall",x+3*k,y+3.07*k,k,27,{size:21,bold:true,color:C.white,align:"center"});
}
function endpoints(s) {
  const [gx,gy]=center(1,2),[tx,ty]=center(5,2);
  dot(s,"Guard start",gx,gy,27,C.green,C.paper,3);
  dot(s,"Geralt goal",tx,ty,27,C.brown,C.paper,3);
  text(s,"Guard",gx-48,gy+19,96,26,{size:19,bold:true,align:"center"});
  text(s,"Geralt",tx-48,ty+19,96,26,{size:19,bold:true,align:"center"});
}
{
  const s=frame("Navigation","Where can the guard walk?");
  rule(s,"Navigation mesh","Connected surfaces that\ncharacters can walk on.",62,195,480);
  rule(s,"Around the wall","The walkable surface\ncontinues past its open end.",62,336,480);
  mapBase(s,false);
  endpoints(s);
  text(s,"Walkable area",615,582,270,32,{size:22,color:C.green,bold:true});
  folio(s,10,"Simplified navigation mesh at the gate");
  notes(s,"Speaker 2","Section 6 · 10:00–13:00",[68,69],[SRC.nav,SRC.astar]);
}
{
  const s=frame("A* pathfinding","Which square should A* explore first?");
  rule(s,"Cost so far","How far the guard would walk\nto reach a position.",62,181,500);
  rule(s,"Estimated cost remaining","How far it might still be\nto Geralt.",62,306,500);
  text(s,"A* explores the most promising\npositions first.",62,458,509,79,{size:27,bold:true,color:C.green});
  mapBase(s,true);
  const [ax,ay]=center(1,2),[rx,ry]=center(2,2),[ux,uy]=center(1,1);
  rect(s,"Promising square",rx-37,ry-37,74,74,C.pale);
  rect(s,"Alternate square",ux-37,uy-37,74,74,"#EFE0BD");
  arrow(s,"Explore ahead",[ax+17,ay],[rx-13,ry],C.green);
  arrow(s,"Keep other option",[ax,ay-17],[ux,uy+13],C.brown);
  endpoints(s);
  folio(s,11,"Simplified A* grid example");
  notes(s,"Speaker 2","Section 6 · continued",[69,72],[SRC.astar]);
}
{
  const s=frame("A* pathfinding","The route around the wall");
  rule(s,"The next square is blocked","A* keeps other positions\navailable to explore.",62,190,490);
  rule(s,"A route through open squares","Once it reaches Geralt, A* can\ntrace the route back to the guard.",62,337,495);
  mapBase(s,true);
  const route=[[1,2],[2,2],[2,1],[2,0],[3,0],[4,0],[4,1],[4,2],[5,2]].map(p=>center(...p));
  line(s,"Final route",route,C.green,8);
  for(const [x,y] of route.slice(1,-1))dot(s,"Route waypoint",x,y,11,C.green);
  endpoints(s);
  folio(s,12,"Simplified A* grid example");
  notes(s,"Speaker 2","Section 6 · continued",[72,74],[SRC.astar]);
}

// 13 — Actual A* search trace
{
  const s=frame("A* pathfinding","A* expands through a maze");
  await photo(s,"astar-demo.gif","An A-star search explores blue cells around dark obstacles and then traces the final route in gold",117,154,483,470);
  const legend = [
    ["#438F48","Start","The search begins in the upper left."],
    ["#B5D8ED","Explored squares","Blue spreads as A* checks more positions."],
    ["#F8C025","Final route","Gold shows the route after A* reaches the goal."],
  ];
  for(const [i,[color,head,body]] of legend.entries()){
    const y=206+i*121;
    rect(s,head+" legend key",663,y+8,24,24,color);
    text(s,head,702,y,507,40,{size:29,bold:true});
    text(s,body,702,y+43,507,39,{size:22,color:C.muted});
  }
  folio(s,13,"Recorded A* search trace · graphfinder");
  s.speakerNotes.text = [
    "Speaker 2  |  Section 6 · continued",
    "Here’s a larger example from a running A-star search. The blue squares show the positions it has explored. When it reaches the red goal, the gold line reveals the route it found.",
    `Source · graphfinder / José L. Salmeron · ${SRC.graphfinder}\nOriginal capture cropped to the grid and frame-sampled for playback.`,
  ].join("\n\n");
}

// 14 — Return to Novigrad for the close
{
  const s=frame(null,null,true);
  await photo(s,"novigrad-crop.jpg","Geralt looking across Novigrad",592,0,688,H);
  rect(s,"Closing text panel",0,0,594,H,C.charcoal);
  text(s,"One encounter\nin Novigrad",62,65,518,152,{size:64,bold:true,color:C.white});
  const recap=[
    ["Frustum culling","Should we draw it for this view?"],
    ["Level of detail","How detailed should it be?"],
    ["Collision detection","What could block this move?"],
    ["Pathfinding","Which route reaches the goal?"],
  ];
  recap.forEach(([head,body],i)=>{
    const y=248+i*94;
    text(s,head,63,y,497,34,{size:25,bold:true,color:C.amber});
    text(s,body,63,y+36,497,32,{size:25,color:C.white});
  });
  notes(s,"Speaker 2","Section 7 · 13:00–14:00",[81,84],[`Novigrad gameplay still · GamePro / CD Projekt Red · ${SRC.city}`],{
    2: script[83].replace("why games can feel a little magical","why game worlds can feel like places we can actually explore"),
  });
}

// 15 — Clickable source list
{
  const s=frame(null,"References");
  const refs=[
    ["CD Projekt Red and Umbra","Solving Visibility in REDengine 3 · GDC 2014",SRC.gdc],
    ["Epic Games","Visibility and occlusion culling",SRC.frustum],
    ["NVIDIA","The Witcher 3 foliage visibility and detail",SRC.foliage],
    ["Box2D","Broad-phase and narrow-phase collision checks",SRC.collision],
    ["CD Projekt Red REDkit","Generating navigation data",SRC.nav],
    ["Hart, Nilsson and Raphael","A Formal Basis for the Heuristic Determination of Minimum Cost Paths",SRC.astar],
    ["Tobias Garpenhall","R.O.S.E. frustum-culling debug capture",SRC.rose],
    ["Raygeas","AZURE Nature tree asset · Unity Asset Store",SRC.azure],
    ["graphfinder","A* maze search animation",SRC.graphfinder],
  ];
  refs.forEach(([head,body,url],i)=>{
    const y=148+i*54;
    text(s,head,62,y,390,31,{size:23,bold:true,color:C.green,link:url});
    text(s,body,456,y,753,31,{size:22,color:C.ink,link:url});
    line(s,"Reference divider",[[62,y+42],[1218,y+42]],"#D0D3C8",1);
  });
  folio(s,15,"Gameplay stills · CD Projekt Red and GamePro");
  notes(s,null,null,null,Object.entries(SRC).map(([label,url])=>`${label} · ${url}`));
}

const raw = path.join(build,"candidate.pptx");
const candidate = path.join(build,"candidate-sections.pptx");
const pptx=await PresentationFile.exportPptx(deck);
await pptx.save(raw);
const sectionResult=spawnSync(python,[path.join(build,"sections.py"),raw,candidate],{encoding:"utf8"});
if(sectionResult.status!==0)throw new Error(sectionResult.stderr || sectionResult.error?.message);
console.log("Saved candidate with",deck.slides.items.length,"slides");
for(const [index,slide] of deck.slides.items.entries()){
  const preview=await deck.export({slide,format:"png",scale:1});
  await fs.writeFile(path.join(build,"previews",`slide-${String(index+1).padStart(2,"0")}.png`),
    new Uint8Array(await preview.arrayBuffer()));
}

const finalPath=path.join(root,"PowerPoint","Video Game Optimization - Novigrad with Demos.pptx");
const { finalizePresentation }=await import(pathToFileURL(path.join(skill,"container_tools/artifact_tool_utils.mjs")).href);
const imported=await PresentationFile.importPptx(await FileBlob.load(candidate));
if(imported.slides.items.length!==15) throw new Error("Slide count did not survive PowerPoint export");
const link=fs.link;
fs.link=async (from,to)=>{
  try {
    await link(from,to);
  } catch (error) {
    // Preserve exclusive publishing on hosts where hard links are unavailable.
    if(error.code!=="EPERM" || to!==finalPath || !from.endsWith(".validated"))throw error;
    await fs.copyFile(from,to,fsConstants.COPYFILE_EXCL);
  }
};
try {
  const result=await finalizePresentation({
    workspaceDir:root,candidatePath:candidate,finalPath,explicitTotalSlideCount:15,
    pythonExecutable:python,
    integrityValidatorPath:path.join(skill,"container_tools/inspect_presentation_package_integrity.py"),
    layoutValidatorPath:path.join(skill,"container_tools/inspect_presentation_layout_geometry.py"),
    layoutArgs:["--expected-slide-size-emu","12192000,6858000","--validate-heading-fit"],
    fontPolicy:{basis:"design",families:[font]},
    verifyArtifactToolImport:false,
    receiptPath:path.join(build,`validation-${Date.now()}.json`),
  });
  console.log(JSON.stringify(result));
} finally {
  fs.link=link;
}
