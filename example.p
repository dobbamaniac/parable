type Particle:
  x: f32
  y: f32
  vx: f32
  vy: f32
  mass: f32

particles = table Particle[1000]

for particle in particles:
  particle.x += particle.vx
  particle.y += particle.vy
