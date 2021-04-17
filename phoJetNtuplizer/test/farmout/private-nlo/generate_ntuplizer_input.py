base_dir = '/hdfs/store/user/mallampalli/analysis/Mono-zprime/signal_generation_farmout/MiniAOD_MonoZprime/actual_files/'

signal_mass_points = {
    1   : [10, 20, 50, 100, 200, 300, 500, 1000, 10000],
    10  : [10, 15, 50, 100, 10000],
    50  : [10, 50, 95, 200, 300, 10000],      
    150 : [10, 200, 295, 500, 1000, 10000],
    500 : [10, 500, 995, 10000],
    1000: [10, 1000, 10000]
}
for mx in signal_mass_points.keys():
     for mzh in signal_mass_points[mx]:
         file_path = base_dir + '%d/%d/renamed_files/'%(mx,mzh)
         ntuplizer_input_file = open('MonoZprime_signal_Mx%d_Mv%d.in'%(mx,mzh),'w+')
         for file_num in range(200):
                file_num = '%04d'%file_num
                file_name = 'MonoZprime_MiniAOD_Mx%d_Mv%d_%s.root'%(mx,mzh,file_num)
                to_write = 'file:'+file_path+file_name+' \n'
                ntuplizer_input_file.write(to_write)

