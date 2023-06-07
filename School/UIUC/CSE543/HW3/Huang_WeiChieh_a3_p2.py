# imports
import os
import sys
import glob
import re
from tkinter.tix import Y_REGION
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from PIL import Image
import random
from scipy.sparse.linalg import svds
#####################################
### Provided functions start here ###
#####################################

# Image loading and saving

def LoadFaceImages(pathname, subject_name, num_images):
    """
    Load the set of face images.  
    The routine returns
        ambimage: image illuminated under the ambient lighting
        imarray: a 3-D array of images, h x w x Nimages
        lightdirs: Nimages x 3 array of light source directions
    """

    def load_image(fname):
        return np.asarray(Image.open(fname))

    def fname_to_ang(fname):
        yale_name = os.path.basename(fname)
        return int(yale_name[12:16]), int(yale_name[17:20])

    def sph2cart(az, el, r):
        rcos_theta = r * np.cos(el)
        x = rcos_theta * np.cos(az)
        y = rcos_theta * np.sin(az)
        z = r * np.sin(el)
        return x, y, z

    ambimage = load_image(
        os.path.join(pathname, subject_name + '_P00_Ambient.pgm'))
    im_list = glob.glob(os.path.join(pathname, subject_name + '_P00A*.pgm'))
    if num_images <= len(im_list):
        im_sub_list = np.random.choice(im_list, num_images, replace=False)
    else:
        print(
            'Total available images is less than specified.\nProceeding with %d images.\n'
            % len(im_list))
        im_sub_list = im_list
    im_sub_list.sort()
    imarray = np.stack([load_image(fname) for fname in im_sub_list], axis=-1)
    Ang = np.array([fname_to_ang(fname) for fname in im_sub_list])

    x, y, z = sph2cart(Ang[:, 0] / 180.0 * np.pi, Ang[:, 1] / 180.0 * np.pi, 1)
    lightdirs = np.stack([y, z, x], axis=-1)
    return ambimage, imarray, lightdirs

def save_outputs(subject_name, albedo_image, surface_normals):
    im = Image.fromarray((albedo_image*255).astype(np.uint8))
    im.save("%s_albedo.jpg" % subject_name)
    im = Image.fromarray((surface_normals[:,:,0]*128+128).astype(np.uint8))
    im.save("%s_normals_x.jpg" % subject_name)
    im = Image.fromarray((surface_normals[:,:,1]*128+128).astype(np.uint8))
    im.save("%s_normals_y.jpg" % subject_name)
    im = Image.fromarray((surface_normals[:,:,2]*128+128).astype(np.uint8))
    im.save("%s_normals_z.jpg" % subject_name)


# Plot the height map

def set_aspect_equal_3d(ax):
    """https://stackoverflow.com/questions/13685386"""
    """Fix equal aspect bug for 3D plots."""
    xlim = ax.get_xlim3d()
    ylim = ax.get_ylim3d()
    zlim = ax.get_zlim3d()
    from numpy import mean
    xmean = mean(xlim)
    ymean = mean(ylim)
    zmean = mean(zlim)
    plot_radius = max([
        abs(lim - mean_)
        for lims, mean_ in ((xlim, xmean), (ylim, ymean), (zlim, zmean))
        for lim in lims
    ])
    ax.set_xlim3d([xmean - plot_radius, xmean + plot_radius])
    ax.set_ylim3d([ymean - plot_radius, ymean + plot_radius])
    ax.set_zlim3d([zmean - plot_radius, zmean + plot_radius])


def display_output(albedo_image, height_map):
    fig = plt.figure()
    plt.imshow(albedo_image, cmap='gray')
    plt.axis('off')
    
    fig = plt.figure(figsize=(10, 10))
    ax = fig.add_subplot(projection='3d')
    ax.view_init(20, 20)
    X = np.arange(albedo_image.shape[0])
    Y = np.arange(albedo_image.shape[1])
    X, Y = np.meshgrid(Y, X)
    H = np.flipud(np.fliplr(height_map))
    A = np.flipud(np.fliplr(albedo_image))
    A = np.stack([A, A, A], axis=-1)
    ax.xaxis.set_ticks([])
    ax.xaxis.set_label_text('Z')
    ax.yaxis.set_ticks([])
    ax.yaxis.set_label_text('X')
    ax.zaxis.set_ticks([])
    ax.yaxis.set_label_text('Y')
    surf = ax.plot_surface(
        H, X, Y, cmap='gray', facecolors=A, linewidth=0, antialiased=False)
    set_aspect_equal_3d(ax)


# Plot the surface normals

def plot_surface_normals(surface_normals):
    """
    surface_normals: h x w x 3 matrix.
    """
    fig = plt.figure()
    ax = plt.subplot(1, 3, 1)
    ax.axis('off')
    ax.set_title('X')
    im = ax.imshow(surface_normals[:,:,0])
    ax = plt.subplot(1, 3, 2)
    ax.axis('off')
    ax.set_title('Y')
    im = ax.imshow(surface_normals[:,:,1])
    ax = plt.subplot(1, 3, 3)
    ax.axis('off')
    ax.set_title('Z')
    im = ax.imshow(surface_normals[:,:,2])


#######################################
### Your implementation starts here ###
#######################################

def preprocess(ambimage, imarray):
    """
    preprocess the data: 
        1. subtract ambient_image from each image in imarray.
        2. make sure no pixel is less than zero.
        3. rescale values in imarray to be between 0 and 1.
    Inputs:
        ambimage: h x w
        imarray: h x w x Nimages
    Outputs:
        processed_imarray: h x w x Nimages
    """
    # print('immarray shape: ', imarray.shape)
    # print('ambient shape: ', ambimage.shape)
    h, w, d = imarray.shape
    subImg = np.empty((h, w, d))

    # step 1, Subtract ambient image from each dimension of imarray
    for Dimension in range(imarray.shape[2]):
        subImg[:,:,Dimension] = imarray[:,:,Dimension] - ambient_image

    # step 2, make sure no negative values
    

    # step 3, rescale values to be between 0 ~ 1
    processed_imarray = np.divide(subImg, 255)
    np.clip(processed_imarray, a_min=0, a_max=None)
    # print('sub shape: ', subImg.shape)
    # print(processed_imarray)
    return processed_imarray


def photometric_stereo(imarray, light_dirs):
    """
    Inputs:
        imarray:  h x w x Nimages
        light_dirs: Nimages x 3
    Outputs:
        albedo_image: h x w
        surface_norms: h x w x 3
    """
    h, w, d = imarray.shape

    newShape = np.reshape(imarray, (h*w, d), order="F")
    newShapeTrans = np.transpose(newShape)
    g = np.linalg.lstsq(light_dirs,newShapeTrans)[0]
    # print('g: ', g.shape)
    adder = np.add((np.power(g[0,:], 2)), (np.power(g[1,:], 2)),(np.power(g[2,:], 2)))
    rho = np.sqrt(adder)
    # print('rho: ', rho.shape)
    albedo_image = np.reshape(rho,(h,w), order="F")
    N = np.divide(g,rho)
    surface_normals = np.reshape(np.transpose(N),[h,w,3])
    # print('surface_normals: ', surface_normals.shape)
    return albedo_image, surface_normals



def get_surface(surface_normals, integration_method):
    """
    Inputs:
        surface_normals:h x w x 3
        integration_method: string in ['average', 'column', 'row', 'random']
    Outputs:
        height_map: h x w
    """
    print('norm: ', surface_normals.shape)
    h, w, d = surface_normals.shape
    height_map = np.zeros((h, w))
    output = np.zeros((h, w))
    output1 = np.zeros((h, w))
    normal_x = surface_normals[:,:,0]
    normal_y = surface_normals[:,:,1]
    normal_z = surface_normals[:,:,2]

    x_deriv = np.divide(normal_x, normal_z)
    y_deriv = np.divide(normal_y, normal_z)
    print(x_deriv.shape)
    x_sum = np.cumsum(x_deriv, axis=0)
    y_sum = np.cumsum(y_deriv)

    match integration_method:
        case 'average':
            print('in average')
            output[1:h, 0] = np.cumsum(y_deriv[1:h, 0])
            output[:, 1:w] = x_deriv[:, 1:w]

            output1[0, 1:w] = np.cumsum(x_deriv[0, 1:w])
            output1[1:h, :] = y_deriv[1:h, :]

            adder = np.add(np.cumsum(output1, axis=1), np.cumsum(output, axis=1))
            height_map = (np.divide(adder, 2))
 
            return height_map
        case 'column':
            output[0, 1:w] = np.cumsum(x_deriv[0, 1:w], axis=0)
            output[:, 1:w] = y_deriv[:, 1:w]
            height_map = np.cumsum(output, axis=1)
            return height_map
        case 'row':
            output[1:h, 0] = np.cumsum(y_deriv[1:h, 0], axis=0)
            output[:, 1:w] = x_deriv[:, 1:w]
            height_map = np.cumsum(output, axis=1)
            return height_map
        case 'random': 
            iteration = 10
            height_map = np.zeros((h,w))
            for x in range(iteration):
                print(x)
                for i in range(h):
                    print(i)
                    for j in range(w):
                        id1 = 0
                        id2 = 0
                        val = 0
                        path = [0] * i + [1] * j
                        random.shuffle(path)
                        for move in path:
                            if move == 0:
                                id1 += 1
                                if id1 > h - 1: id1 -= 1
                                val += y_deriv[id1][id2]
                            if move == 1:
                                id2 += 1
                                if id2 > w - 1: id2 -= 1
                                val += x_deriv[id1][id2]
                        height_map[i][j] += val
            height_map = height_map / iteration

            return height_map
    # imx = surface_normals.shape[1]
    # imy = surface_normals.shape[0] #flipped for indexing
    # #height_map = np.zeros((imx,imy)
    # fx = surface_normals[:,:,0] / surface_normals[:,:,2]
    # fy = surface_normals[:,:,1] / surface_normals[:,:,2]
    # fy = np.nan_to_num(fy)
    # fx = np.nan_to_num(fx)
    # row = np.cumsum(fx,axis=1)
    # column = np.cumsum(fy,axis=0)
    # if integration_method == 'row':
    #     row_temp = np.vstack([row[0,:]]*imy)
    #     height_map = column + row_temp     
    #     #print(np.max(height_map))
    # return height_map



# Main function
if __name__ == '__main__':
    root_path = 'croppedyale/' 
    subject_name = 'yaleB02'
    integration_method = 'row'
    save_flag = True

    full_path = '%s%s' % (root_path, subject_name)
    ambient_image, imarray, light_dirs = LoadFaceImages(full_path, subject_name,
                                                        64)

    processed_imarray = preprocess(ambient_image, imarray)

    albedo_image, surface_normals = photometric_stereo(processed_imarray,
                                                    light_dirs)

    height_map = get_surface(surface_normals, 'row')

    if save_flag:
        save_outputs(subject_name, albedo_image, surface_normals)

    plot_surface_normals(surface_normals)

    display_output(albedo_image, height_map)




