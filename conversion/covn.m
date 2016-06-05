function covn(ima, fname)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Riddhish Bhalodia
% ima : input 3d data
% fname : output file name .nii file
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
dim = size(ima);
mat = [1 0 0 -128.75; 0 1 0 -146.75; 0 0 1 -73.25; 0 0 0 1];

V = struct('fname', fname,...
            'dim', dim,...
            'mat', mat,...
            'pinfo', [1;0;0],...
            'dt', [spm_type('float64') 'BE'],...
            'n', [1 1]);
        
spm_write_vol(V,ima)