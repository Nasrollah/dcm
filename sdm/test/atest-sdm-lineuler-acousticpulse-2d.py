import coolfluid as cf

### Create new model specialized for SD
model   = cf.root.create_component('accousticpulse_2d','cf3.dcm.Model');

### Load the mesh
mesh = model.domain.load_mesh(file = cf.URI('../../../resources/circle-quad-p1-32.msh'), name = 'circle');
model.build_faces();

### Add the Partial Differential Equations to solve
lineuler = model.add_pde(name='lineuler',type='cf3.dcm.equations.lineuler.LinEuler2D',
    shape_function='cf3.dcm.core.LegendreGaussEndP1')
lineuler.gamma = 1.4
rho0 = 1.
U0=[0.,0.]
p0=1.

lineuler.add_term( name='rhs', type='cf3.sdm.br2.lineuler_RightHandSide2D' )

### Add BC
lineuler.add_bc( name='farfield',
                 type='cf3.dcm.equations.lineuler.BCFarfield2D',
                 regions=[ mesh.topology.boundary ] )

### Initialize the solution
model.tools.init_field.init_field(
  field=lineuler.solution,
  functions=[
    '0.001*exp( -( (x)^2 + (y)^2 )/(0.05)^2 )',
    '0',
    '0',
    '1.4 * 0.001*exp( -( (x)^2 + (y)^2 )/(0.05)^2 )' ] )

model.tools.init_field.init_field(
  field=lineuler.background,
  functions=[ str(rho0), str(U0[0]), str(U0[1]), str(p0) ] )

model.tools.init_field.init_field(
  field=lineuler.bdry_background,
  functions=[ str(rho0), str(U0[0]), str(U0[1]), str(p0) ] )

### Create the Solver for the Partial Differential Equations
solver = model.add_solver(name='rk_solver',pde=lineuler)
solver.children.time_step_computer.cfl = 0.2
solver.options.order = 3

### Time Stepping
model.time_stepping.end_time = 0.3
model.time_stepping.execute()


#######################################
# POSTPROC to check accuracy
#######################################
exact_solution = lineuler.fields.create_field(name='exact_solution',variables='rho_ex[s],U_ex[v],p_ex[s]')
init_acousticpulse = model.tools.create_component('init_acousticpulse','cf3.dcm.equations.lineuler.InitAcousticPulse')
init_acousticpulse.field = exact_solution
init_acousticpulse.time = 0.3
init_acousticpulse.execute()

solution = lineuler.fields.solution

difference = lineuler.fields.create_field(name='difference',variables='drho[s],dU[v],dp[s]')
for i in range(len(difference)) :
    difference[i][0] = exact_solution[i][0] - solution[i][0]
    difference[i][1] = exact_solution[i][1] - solution[i][1]/rho0
    difference[i][2] = exact_solution[i][2] - solution[i][2]/rho0
    difference[i][3] = exact_solution[i][3] - solution[i][3]

compute_norm = model.tools.create_component('compute_norm','cf3.solver.ComputeLNorm')
compute_norm.field = difference
compute_norm.order = 2
compute_norm.execute()
print "norm = ",compute_norm.properties()['norm']

########################
# OUTPUT
########################

fields = [
  lineuler.fields.solution.uri(),
  lineuler.fields.wave_speed.uri(),
  lineuler.fields.rhs.uri(),
  lineuler.fields.exact_solution.uri(),
  lineuler.fields.difference.uri()
]

mesh.write_mesh(file=cf.URI('file:lineuler-acousticpulse-2d.plt'),fields=fields)
mesh.write_mesh(file=cf.URI('file:lineuler-acousticpulse-2d.msh'),fields=fields)

